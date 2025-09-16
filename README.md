*Klangstrom* (KLST) is a subtractive infrastructure design framework to facilitate generative, networked, embedded sound + music + composition. *klangstrom* is comprised of two software libraries ( *klang* a node+text-based sound synthesis library and *strom* a node+text-based generative composition library ), an embedded hardware platform, and a programming environment to allow seamless development of generative, networked, embedded sound + music + composition applications.

Project Documentation at []([url](https://klangstrom-for-arduino.dennisppaul.de))

---

⚠️ WIP update documentation below ⚠️

- install [Arduino IDE](https://www.arduino.cc/en/software/#ide)
- start *Arduino IDE**
- install board definitions. go to `Tools > Board:... > Board Manager...` select `STM32 MCU based board`
- install klangstrom with installer script `/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Klangstrom/klangstrom-arduino/main/install.sh)"` ( <- ⚠️⚠️⚠️ WIP not finished ⚠️⚠️⚠️ )

## Install Emulator (WIP)

- install [Umfeld](https://github.com/dennisppaul/umfeld) with installer script `/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/dennisppaul/umfeld/refs/heads/main/install.sh)"`
- @TODO( maybe add klangstrom-emulator as library? )

## Structure

```sh
klangstrom-arduino
├── libraries # `klangstrom-libraries` copied to arduino libraries
│   ├── Klangstrom
│   ├── Klangstrom_KLST_EMU
│   ├── Klangstrom_KLST_PANDA_STM32
│   ├── Klangstrom_KLST_PANDA_STM32_CubeMX
│   ├── USBDevices
│   ├── USBHost # <- WIP not working ATM, do not copy
│   └── klangwellen
├── install.sh # installs libs and variants ( added only to the public repo )
├── tools
│   ├── append-board-variant-definition.sh
│   ├── klangstrom-libraries.config
│   ├── klangstrom-tools.config
│   ├── klst-serialmonitor
│   ├── link_libraries.sh
│   ├── link_variant_files.sh
│   ├── link-klangstrom-arduino-libraries-from-klangstrom-arduino.sh
│   ├── link-klangstrom-arduino-variants-into-stm32duino.sh
│   ├── remove_linked_variant_files.sh
│   └── stm32duino.config
└── variants # variants files added to STM32duino via script 
    ├── KLST_PANDA 
    └── KLST_CATERPILLAR
```

