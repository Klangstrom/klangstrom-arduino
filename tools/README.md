a set of tools used for development.

- `klst-serialmonitor` :: tries to start a serial monitor `screen` session in the console based on a *typical* STLINK device name ( `screen` sessions can be quit with `CTRL+A` + `CTRL+K` + `Y` )
- `link-klangstrom-arduino-libraries-from-klangstrom-arduino.sh` :: create symlink from klangstrom libraries into Arduino library folder
- `link-klangstrom-arduino-variants-into-stm32duino.sh` :: creates symlinks from variant files into STM32duino hardware definitions folder ( may need to adapt STM32duino path in `stm32duino.config` )
