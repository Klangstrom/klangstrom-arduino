#!/bin/zsh

SCRIPT_PATH="$(cd "$(dirname "$0")" && pwd)"
source "$SCRIPT_PATH/klangstrom-tools.config"
KLST_TOOLS_PATH="$(cd "$CONFIG_DIR/$KLST_TOOLS_PATH_RELATIVE" && pwd)"
KLST_ARDUINO_PATH="$(cd "$CONFIG_DIR/$KLST_ARDUINO_PATH_RELATIVE" && pwd)"

# TODO WIP this is macOS only for now

SRC="$KLST_ARDUINO_PATH/libraries"
DST="$HOME/Documents/Arduino/libraries"
echo
echo "linking libraries from '$SRC' into '$DST'"
echo 
"$SCRIPT_PATH/link_libraries.sh" klangstrom-libraries.config $SRC $DST
