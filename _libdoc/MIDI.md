---
layout: libdoc
title: MIDI
permalink: /midi/
index: 20
---

KLST_PANDA features a so-called *analog* or serial MIDI interface for intput and output via two *audio jacks* ( see [Technical Specifications](/tech-specs) ):

- ㉑ :: MIDI out ( analog )
- ㉒ :: MIDI in ( analog )

```c
void midi_note_on(uint8_t channel, uint8_t note, uint8_t velocity);
void midi_note_off(uint8_t channel, uint8_t note, uint8_t velocity);
void midi_event(SerialDevice* serial_device);

bool midi_init();
void midi_deinit();
void midi_send(const uint8_t* data, uint16_t length);
```

@TODO( MIDI is missing some callbacks basic callbacks like `midi_sysex`, `midi_control_change`, `midi_program_change` and clock functions )

note, that there is also a USB-based MIDI interface, that allows to connect the board as a USB device to a host or act as a host for USB MIDI devices.

## Example `MIDI`

```c
{% include_relative code/MIDI.ino %}
```
