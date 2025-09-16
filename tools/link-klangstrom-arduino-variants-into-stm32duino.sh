#!/bin/zsh
SCRIPT_PATH="$(cd "$(dirname "$0")" && pwd)"
CONFIG_PATH="$SCRIPT_PATH/stm32duino.config"
if [ -f "$CONFIG_PATH" ]; then
    source "$CONFIG_PATH"
else
    echo "⚠️ stm32duino.config not found! Please run install-dependencies.sh first."
    exit 1
fi
source "$SCRIPT_PATH/klangstrom-tools.config"
KLST_TOOLS_PATH="$SCRIPT_PATH/$KLST_TOOLS_PATH_RELATIVE"
KLST_ARDUINO_PATH="$SCRIPT_PATH/$KLST_ARDUINO_PATH_RELATIVE"
VARIANTS_SOURCE_PATH="$KLST_ARDUINO_PATH/variants"

update_variant() {
    echo "======================="
    echo $1
    echo "======================="
    VARIANT_PATH="$VARIANTS_SOURCE_PATH/$1"
    BOARD_FILE="$1-boards.txt"
    
    echo "updating board definition +"
    "$SCRIPT_PATH/append-board-variant-definition.sh" "$VARIANT_PATH/$BOARD_FILE"
    echo "(re-)creating symlinks at : $ARDUINO_STM32DUINO_PATH"
    "$SCRIPT_PATH/link_variant_files.sh" "$VARIANT_PATH/variant" "$ARDUINO_STM32DUINO_PATH"
}

echo "======================="
echo "KLST STM32 board update"
echo "======================="

if [ -d "$ARDUINO_STM32DUINO_PATH" ]; then
  echo "found variant defintion at: $ARDUINO_STM32DUINO_PATH"
else
  echo "could not find variant defintion at: $ARDUINO_STM32DUINO_PATH"
  exit -1
fi

echo "removing all symlinks"
"$SCRIPT_PATH/remove_linked_variant_files.sh" "$ARDUINO_STM32DUINO_PATH"

update_variant KLST_CATERPILLAR
update_variant KLST_PANDA
