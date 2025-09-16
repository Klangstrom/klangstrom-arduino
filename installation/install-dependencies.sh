#!/usr/bin/env bash
set -euo pipefail
IFS=$'\n\t'

COMMON_TMP=$(mktemp)
curl -fsSL "https://raw.githubusercontent.com/${REPO:-Klangstrom/klangstrom-arduino}/${KLST_REF:-main}/installation/common.sh" -o "$COMMON_TMP"
# shellcheck source=/dev/null
. "$COMMON_TMP"
rm -f "$COMMON_TMP"

require_curl() {
  if ! command -v curl >/dev/null 2>&1; then
    echo "ERROR: 'curl' is not installed. Please install curl and try again." >&2
    echo
    echo "on Debian/Ubuntu   : sudo apt-get install curl"
    echo "on Arch Linux      : sudo pacman -Syu curl"
    echo "on Windows (UCRT64): pacman -Syu curl"
    exit 1
  fi
}

# Robust fetch to a temp file + minimal integrity checks
fetch() {
  # usage: fetch <url> <outfile>
  local url=$1 out=$2
  curl --fail --show-error --silent --location \
       --connect-timeout 10 --max-time 300 \
       --retry 3 --retry-delay 2 --retry-connrefused \
       "$url" -o "$out"
  # Sanity checks: non-empty and looks like a script
  if [[ ! -s "$out" ]]; then
    echo "ERROR: downloaded file is empty: $url" >&2
    exit 1
  fi
  if ! head -n1 "$out" | grep -qE '^#!'; then
    echo "ERROR: downloaded file is not a script (missing shebang): $url" >&2
    exit 1
  fi
}

run_remote() {
  # usage: run_remote <relative-script-name>
  local rel=$1 tmp
  tmp=$(mktemp)
  fetch "${BASE_URL}/${rel}" "$tmp"
  # Ensure newly installed binaries in child scripts become visible
  hash -r
  bash "$tmp"
  rm -f "$tmp"
}

is_raspberry_pi() {
  # Handle various places the model string may exist
  if grep -qi raspberry /proc/device-tree/model 2>/dev/null; then
    return 0
  fi
  if grep -qi raspberry /sys/firmware/devicetree/base/model 2>/dev/null; then
    return 0
  fi
  return 1
}

require_curl

echo "-------------------------------------------"
printf -- "--- platform: "

case "$(uname -s)" in
  Darwin)
    echo "detected macOS"
    run_remote "install-macOS.sh"
    ;;

  Linux)
    if is_raspberry_pi; then
      echo "detected Raspberry Pi"
      run_remote "install-raspberry-pi.sh"
    elif [[ -f /etc/arch-release ]] || grep -qi '^ID=arch' /etc/os-release 2>/dev/null; then
      echo "detected Arch Linux"
      run_remote "install-arch.sh"
    else
      echo "detected Linux"
      run_remote "install-linux.sh"
    fi
    ;;

  MINGW*|MSYS*|CYGWIN*)
    if [[ "${MSYSTEM:-}" == "UCRT64" ]]; then
      echo "detected Windows (MSYS2 UCRT64)"
      run_remote "install-windows-ucrt64.sh"
    else
      echo "unsupported Windows environment. Please use MSYS2 UCRT64." >&2
      exit 1
    fi
    ;;

  *)
    echo "unsupported platform: $(uname -s)" >&2
    exit 1
    ;;
esac
