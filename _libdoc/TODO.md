---
layout: libdoc
title: TODO
permalink: /todo/
index: 99
---

the following topics have demos and files and APIs

## AudioCodec

- `AudioBlock`
- `AudioInfo`
- `AudioDevice`

## Time

- `Beat`
- `Timer`
- `ClockCycles` ( in `System` )
- `Ticks` ( in `System` )

## Console

- `Console`

## DACADC

- `DACADC`

## Display

- `BitmapFont`
- `Display`
- `Draw`

## Encoder

- `Encoder`

## IDC

@NOTE( *IDC* stands for *Inter-Device Connection* and incidentally also uses a *Insulation-Displacement Contact* )

- `SerialDevice`

## Key

- `Key`

## LED

- `LED`

## Microphone

@TODO(is this the MEMS mic?!?)

- `Microphone`

## MIDI

@NOTE(this is the analog/serial MIDI port)

- `MIDI` @TODO( <- missing some callbacks?!? )
- `KlangstromMIDIParser` @TODO( <- include this? )

## SDCard

- `SDCard`
- @TODO(add demo that streams WAV <- this already exists in Advanced )
- @TODO(add demo that loads WAV)

## System

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

## Tasks + Timers

- `TaskScheduler`
- `Timers`

---

# ==MAYBE==

## Utilities+Tools

- `embedded_cli`
- `Tools`