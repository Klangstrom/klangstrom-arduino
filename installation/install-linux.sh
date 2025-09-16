#!/usr/bin/env bash

set -euo pipefail
IFS=$'\n\t'

log(){ printf "%s\n" "$*"; }

# --- Ensure we're on an apt-based distro -------------------------------------
if ! command -v apt-get >/dev/null 2>&1; then
  echo "ERROR: This installer targets Debian/Ubuntu (apt). For Arch use the Arch script, for RPi use the Pi script." >&2
  exit 1
fi

# --- Sudo warmup + keepalive (auto-cleans on exit) ---------------------------
log "--- requesting sudo access once"
sudo -v
KEEP_SUDO_ALIVE_PID=
{
  while true; do
    sudo -n true 2>/dev/null || exit
    sleep 60
  done
} &
KEEP_SUDO_ALIVE_PID=$!
cleanup_keepalive(){ [[ -n "${KEEP_SUDO_ALIVE_PID:-}" ]] && kill "$KEEP_SUDO_ALIVE_PID" 2>/dev/null || true; }
trap cleanup_keepalive EXIT

export DEBIAN_FRONTEND=noninteractive

log "OK, WE ARE ON LINUX"
log "abort for now ... ⚠️⚠️️⚠️ WIP ⚠️⚠️⚠️"
exit 0

