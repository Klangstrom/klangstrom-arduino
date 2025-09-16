#!/usr/bin/env bash
set -euo pipefail
IFS=$'\n\t'
PROJECT_NAME=klangstrom-arduino

# --- early requirements -------------------------------------------------------
if ! command -v curl >/dev/null 2>&1; then
  echo "ERROR: 'curl' is not installed. Please install curl and try again." >&2
  exit 1
fi

# --- optional: parse --ref <ref> before loading common.sh ---------------------
if [[ $# -ge 2 && "$1" == "--ref" ]]; then
  KLST_REF="$2"
  shift 2
fi
: "${REPO:=Klangstrom/$PROJECT_NAME}"      # allow override via env
: "${KLST_REF:=main}"

# --- load common config (builds BASE_URL/BUNDLE_URL) --------------------------
COMMON_TMP=$(mktemp)
curl -fsSL "https://raw.githubusercontent.com/${REPO}/${KLST_REF}/installation/common.sh" -o "$COMMON_TMP"
# shellcheck source=/dev/null
. "$COMMON_TMP"
rm -f "$COMMON_TMP"

# --- temp files + cleanup -----------------------------------------------------
TMP_DEP=$(mktemp)
TMP_UMF=$(mktemp)
cleanup() { rm -f "$TMP_DEP" "$TMP_UMF"; }
trap cleanup EXIT

fetch() {
  local url=$1 out=$2
  curl --fail --show-error --silent --location \
       --connect-timeout 10 --max-time 300 \
       --retry 3 --retry-delay 2 --retry-connrefused \
       -o "$out" "$url"
  [[ -s "$out" ]] || { echo "ERROR: downloaded file is empty: $url" >&2; exit 1; }
  head -n1 "$out" | grep -qE '^#!' || { echo "ERROR: not a script (missing shebang): $url" >&2; exit 1; }
}

run_script() {
  local path=$1
  hash -r
  bash "$path"
}

echo "---------------------------------"
echo "--- installing dependencies"
echo "---------------------------------"
echo 
fetch "${BASE_URL}/install-dependencies.sh" "$TMP_DEP"
run_script "$TMP_DEP"
echo
echo "---------------------------------"
echo "--- installing $PROJECT_NAME"
echo "---------------------------------"
echo
fetch "${BASE_URL}/install-$PROJECT_NAME.sh" "$TMP_UMF"
# pass --tag only when ref != main
if [[ "$KLST_REF" != "main" ]]; then
  bash "$TMP_UMF" --tag "$KLST_REF"
else
  run_script "$TMP_UMF"
fi
echo
echo "---------------------------------"
echo "--- installation complete"
echo "---------------------------------"