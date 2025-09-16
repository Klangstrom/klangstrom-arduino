#!/usr/bin/env bash

set -euo pipefail
IFS=$'\n\t'

# defaults (overridable by flags)
AUTO_YES=false
TARGET_DIR="$(pwd)"
TAG=""
DEPTH=""

usage() {
  cat <<'EOF'
Usage: install-klangstrom-arduino.sh [options]

Options:
  -y, --yes                 Non-interactive; accept prompts
      --install-dir <path>  Installation directory (default: current directory)
      --tag <vX.Y.Z|ref>    Tag/ref to clone
      --depth <N>           Shallow clone depth (positive integer)
  -h, --help                Show this help and exit

Examples:
  ./install-klangstrom-arduino.sh
  ./install-klangstrom-arduino.sh --tag v2.4.0 --depth 1 -y
  ./install-klangstrom-arduino.sh --install-dir /opt/klangstrom-arduino -y
EOF
}

# ---- parse args -------------------------------------------------------------
if [[ $# -gt 0 ]]; then
  while [[ $# -gt 0 ]]; do
    case "$1" in
      -y|--yes) AUTO_YES=true; shift ;;
      --install-dir)
        [[ $# -ge 2 ]] || { echo "ERROR: --install-dir needs a path" >&2; exit 1; }
        TARGET_DIR=$2; AUTO_YES=true; shift 2 ;;
      --tag)
        [[ $# -ge 2 ]] || { echo "ERROR: --tag needs a value" >&2; exit 1; }
        TAG=$2; shift 2 ;;
      --depth)
        [[ $# -ge 2 ]] || { echo "ERROR: --depth needs a value" >&2; exit 1; }
        DEPTH=$2
        if ! [[ "$DEPTH" =~ ^[1-9][0-9]*$ ]]; then
          echo "ERROR: --depth must be a positive integer" >&2
          exit 1
        fi
        shift 2 ;;
      -h|--help) usage; exit 0 ;;
      *)
        echo "Unknown option: $1" >&2
        usage; exit 1 ;;
    esac
  done
fi

# ---- prerequisites ----------------------------------------------------------
if ! command -v git >/dev/null 2>&1; then
  echo "ERROR: 'git' is not installed. Please install git and try again." >&2
  echo "  macOS            : brew install git"
  echo "  Debian/Ubuntu    : sudo apt-get install git"
  echo "  Windows (MSYS2)  : pacman -S git"
  exit 1
fi

# ---- confirm/install-dir ----------------------------------------------------
if [[ "$AUTO_YES" == false ]]; then
  printf "Install Klangstrom for Arduino into: '%s' ? [Y/n] ( waiting for 20sec )" "$TARGET_DIR"
  if read -r -t 20 confirm; then
    confirm=$(printf "%s" "${confirm:-}" | tr '[:upper:]' '[:lower:]')
  else
    confirm="y"
    echo    # move to next line after timeout
  fi

  if [[ "$confirm" =~ ^(n|no)$ ]]; then
    # -e (readline) if available on this bash
    if [[ ${BASH_VERSINFO[0]} -gt 4 || ( ${BASH_VERSINFO[0]} -eq 4 && ${BASH_VERSINFO[1]} -ge 4 ) ]]; then
      read -erp "Enter a different installation path: " custom_path
    else
      read -rp  "Enter a different installation path: " custom_path
    fi
    [[ -n "${custom_path:-}" ]] && TARGET_DIR=$custom_path
  fi
fi

# Create target dir if needed
if [[ ! -d "$TARGET_DIR" ]]; then
  echo "Creating directory: $TARGET_DIR"
  mkdir -p "$TARGET_DIR"
fi

# Abort if a non-empty 'klangstrom-arduino' dir already exists
if [[ -d "$TARGET_DIR/klangstrom-arduino" ]] && [[ -n "$(ls -A "$TARGET_DIR/klangstrom-arduino" 2>/dev/null || true)" ]]; then
  echo "Warning: '$TARGET_DIR/klangstrom-arduino' already exists and is not empty. Aborting." >&2
  exit 1
fi

cd "$TARGET_DIR"

echo "-------------------------------------------"
echo "--- cloning klangstrom-arduino repositories"
echo "-------------------------------------------"

# ---- helpers ---------------------------------------------------------------
version_ge() {
  # returns 0 (true) if $1 >= $2 (semver-ish)
  [[ "$(printf '%s\n' "$1" "$2" | sort -V | head -n1)" == "$2" ]]
}

retry_git() {
  # usage: retry_git <git> <args...>
  local attempt=1
  local max=3
  until "$@"; do
    rc=$?
    if (( attempt >= max )); then
      echo "ERROR: git command failed after $max attempts: $*" >&2
      return "$rc"
    fi
    echo "git failed (rc=$rc). Retrying in 2s... (attempt $((attempt+1))/$max)"
    sleep 2
    attempt=$(( attempt + 1 ))
  done
}

# Prepare common clone speedups (safe for old gits; unknown options are errors, hence guarded)
FILTER_OPTS=(--filter=blob:none)
SINGLE_BRANCH=("--single-branch")

# Prepare per-repo args
KLST_CLONE_ARGS=("${FILTER_OPTS[@]}" "${SINGLE_BRANCH[@]}")

# Apply tag/ref
if [[ -n "$TAG" ]]; then
  TAG_CLEAN="${TAG#v}"
  KLST_CLONE_ARGS+=(--branch "$TAG")
fi

# Apply depth/shallow options
if [[ -n "$DEPTH" ]]; then
  echo "Using depth '$DEPTH' for all repositories"
  KLST_CLONE_ARGS+=(--depth "$DEPTH")
fi

# Environment to avoid interactive prompts
export GIT_TERMINAL_PROMPT=0
export GIT_ASKPASS=echo

# If empty directories already exist (e.g., created earlier), remove them so clone can proceed
for d in klangstrom-arduino; do
  if [[ -d "$d" ]] && [[ -z "$(ls -A "$d" 2>/dev/null || true)" ]]; then
    rmdir "$d" || true
  fi
done

# ---- clone -----------------------------------------------------------------
retry_git git clone "${KLST_CLONE_ARGS[@]}"      https://github.com/Klangstrom/klangstrom-arduino

echo "-------------------------------------------"
echo "--- download complete"
echo "-------------------------------------------"
