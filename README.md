*Klangstrom* (KLST) is a subtractive infrastructure design framework to facilitate generative, networked, embedded sound + music + composition. *klangstrom* is comprised of two software libraries ( *klang* a node+text-based sound synthesis library and *strom* a node+text-based generative composition library ), an embedded hardware platform, and a programming environment to allow seamless development of generative, networked, embedded sound + music + composition applications.

find documentation at [klangstrom-for-arduino.dennisppaul.de](https://klangstrom-for-arduino.dennisppaul.de).

## Install Board (WIP)

⚠️ WIP needs update ⚠️

- install [Arduino IDE](https://www.arduino.cc/en/software/#ide)
- install [STM32duino / Arduino_Core_STM32](https://github.com/stm32duino/Arduino_Core_STM32?tab=readme-ov-file#getting-started)
- open console and copy-paste [klangstrom-arduino](https://github.com/Klangstrom/klangstrom-arduino) installer below:

```sh
https://raw.githubusercontent.com/Klangstrom/klangstrom-arduino/main/install.sh)"` ( <- ⚠️ WIP not finished ⚠️ )
```

## Install Emulator (WIP)

⚠️ WIP needs update ⚠️

- install [Umfeld](https://github.com/dennisppaul/umfeld)https://github.com/dennisppaul/umfeld?tab=readme-ov-file#quickstart)
- open console and copy-paste [klangstrom-arduino](https://github.com/Klangstrom/klangstrom-arduino) installer below:

```sh
https://raw.githubusercontent.com/Klangstrom/klangstrom-arduino/main/install.sh)"` ( <- ⚠️ WIP not finished ⚠️ )
```

## Structure

```sh
klangstrom-arduino
├── libraries      # added to Arudino library folder, copy from `klangstrom-libraries`
│   ├── Klangstrom
│   ├── Klangstrom_Emulator
│   ├── Klangstrom_KLST_EMU
│   ├── Klangstrom_KLST_PANDA_STM32
│   ├── Klangstrom_KLST_PANDA_STM32_CubeMX
│   ├── USBDevices # ( ⚠️ WIP not working ATM ⚠️ )
│   └── USBHost    # ( ⚠️ WIP not working ATM ⚠️ )
├── install.sh     # installs libraries and variants
├── tools
│   ├── append-board-variant-definition.sh
│   ├── klangstrom-libraries.config
│   ├── klangstrom-tools.config
│   ├── klst-serialmonitor
│   ├── link_libraries.sh
│   ├── link_variant_files.sh
│   ├── link-klangstrom-arduino-libraries-from-klangstrom-arduino.sh
│   ├── link-klangstrom-arduino-variants-into-stm32duino.sh
│   ├── README.md
│   ├── remove_linked_variant_files.sh
│   └── stm32duino.config
└── variants         # variants files copy and appended to STM32duino via script 
    ├── KLST_PANDA 
    └── KLST_CATERPILLAR
```

