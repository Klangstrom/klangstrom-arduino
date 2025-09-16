---
layout: libdoc
title: System
permalink: /system/
index: 101
---

`system_init()` should be called, before any other peripherals are initialized or used.

```c
void                       system_init()
void                       system_register_audiodevice(AudioDevice* audiodevice)
ArrayList_AudioDevicePtr*  system_get_registered_audiodevices()
void                       system_register_serialdevice(SerialDevice* serialdevice)
ArrayList_SerialDevicePtr* system_get_registered_serialdevices()
void                       system_register_gpio_listener(GPIOListener* gpio_listener)
ArrayList_GPIOListenerPtr* system_get_registered_gpio_listener()
void                       system_register_timer(Timer* timer)
ArrayList_TimerPtr*        system_get_registered_timer()
uint16_t                   system_get_unique_device_ID()
bool                       system_is_initialized()
uint32_t                   system_get_ticks()
void                       system_enable_cycle_counter(bool enable)
void                       system_reset_cycles()
uint32_t                   system_get_cycles()
uint32_t                   system_clock_frequency()
float                      system_cycles_to_micros(uint32_t cycles)
AudioDevice*               system_init_audiocodec();
```

- `system_jump_to_bootloader()` still working?
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
