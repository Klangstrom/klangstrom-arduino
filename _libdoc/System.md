---
layout: libdoc
title: System
permalink: /system/
index: 101
---

System

```cpp
```

- `System`
    - `SystemUID` @NOTE(included in `System`)
- `SystemBoot` @TODO(<- does this still work?)
- `Klangstrom` ( "include 'Klangstrom.h' in every project" )
- DEMO mit `PeripheralConfiguration_CUSTOM.h`?!? ( "activate specfic peripherals:" )
    ```c
    #define KLST_PERIPHERAL_ENABLE_GPIO
    #define KLST_PERIPHERAL_ENABLE_SERIAL_DEBUG
    #define KLST_PERIPHERAL_ENABLE_AUDIODEVICE
    #define KLST_PERIPHERAL_ENABLE_LEDS
    #define KLST_PERIPHERAL_ENABLE_SD_CARD
    #define KLST_PERIPHERAL_ENABLE_IDC_SERIAL
    #define KLST_PERIPHERAL_ENABLE_ON_BOARD_MIC
    #define KLST_PERIPHERAL_ENABLE_TIMERS
    #define KLST_PERIPHERAL_ENABLE_ENCODER
    #define KLST_PERIPHERAL_ENABLE_MECHANICAL_KEYS
    #define KLST_PERIPHERAL_ENABLE_MIDI
    #define KLST_PERIPHERAL_ENABLE_ADC_DAC
    #define KLST_PERIPHERAL_ENABLE_EXTERNAL_MEMORY
    #define KLST_PERIPHERAL_ENABLE_DISPLAY
    ```
- GPIO?!?
