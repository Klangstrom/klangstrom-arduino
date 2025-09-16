#!/usr/bin/env bash

set -euo pipefail
IFS=$'\n\t'

COMMON_TMP=$(mktemp)
curl -fsSL "https://raw.githubusercontent.com/${REPO:-Klangstrom/klangstrom-arduino}/${KLST_REF:-main}/installation/common.sh" -o "$COMMON_TMP"
# shellcheck source=/dev/null
. "$COMMON_TMP"
rm -f "$COMMON_TMP"

# --- Helpers ------------------------------------------------------------------
log(){ printf "%s\n" "$*"; }

log "OK, WE ARE ON MACOS"
log "abort for now ... ⚠️⚠️️⚠️ WIP ⚠️⚠️⚠️"
exit 0
