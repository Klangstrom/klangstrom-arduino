#!/usr/bin/env bash

set -euo pipefail
IFS=$'\n\t'

log(){ printf "%s\n" "$*"; }

# --- Environment check --------------------------------------------------------
if [[ "${MSYSTEM:-}" != "UCRT64" ]]; then
  echo "ERROR: Run this from the MSYS2 UCRT64 shell." >&2
  echo "Open 'MSYS2 UCRT64' from the Start menu and re-run." >&2
  exit 1
fi

# Helpful: show key paths
log "--- environment"
log "MSYSTEM=${MSYSTEM}"
log "PATH=${PATH}"

log "OK, WE ARE ON WINDOWS"
log "abort for now ... ⚠️⚠️️⚠️ WIP ⚠️⚠️⚠️"
exit 0
