#!/bin/zsh

SCRIPT_PATH="$(cd "$(dirname "$0")" && pwd)"
source "$SCRIPT_PATH/klangstrom-tools.config"
KLST_TOOLS_PATH="$SCRIPT_PATH/$KLST_TOOLS_PATH_RELATIVE"
KLST_ARDUINO_PATH="$SCRIPT_PATH/$KLST_ARDUINO_PATH_RELATIVE"

# TODO WIP this is macOS only for now

SRC="$KLST_ARDUINO_PATH/libraries"
DST="$HOME/Documents/Arduino/libraries"
echo
echo "linking libraries from '$SRC' into '$DST'"
echo 
"$SCRIPT_PATH/link_libraries.sh" "$SCRIPT_PATH/klangstrom-libraries.config" $SRC $DST
