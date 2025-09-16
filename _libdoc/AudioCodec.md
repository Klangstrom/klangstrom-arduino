---
layout: libdoc
title: Audio Codec
permalink: /audiocodec/
index: 10
---

audio codec is an audio device that takes care of receiving and transmitting audio sample data to the analog input and outputs.

## `AudioDevice`

on KLST_PANDA the default audio device can be intialized with `system_init_audiocodec()`. this initializes the audio device connected to *audio jacks* on KLST_PANDA ( see [Technical Specifications](/tech-specs) ):

- ⑭ :: line out
- ⑮ :: line in
- ⑯ :: headphones + mic
- ⑰ :: microphone in

`AudioDevice` implements the following functions:

```c
void audioblock(AudioBlock* audio_block)

AudioDevice* audiodevice_init_audiocodec(AudioInfo* audioinfo)
void         audiodevice_deinit(AudioDevice* audiodevice)
void         audiodevice_resume(AudioDevice* audiodevice)
void         audiodevice_pause(AudioDevice* audiodevice)
void         audiodevice_setup_device(AudioDevice* audiodevice)
AudioDevice* audiodevice_create_from_audioinfo(AudioInfo* audioinfo)
```

## `AudioInfo`

structure that can be used to initalize an audio device with `audiodevice_init_audiocodec(AudioInfo*)`. properties like sample rate and in- and output channels can be specified.

```c
uint32_t sample_rate
uint8_t  output_channels
uint8_t  input_channels
uint16_t block_size
uint8_t  bit_depth
uint8_t  device_type
uint8_t  device_id
```

## `AudioBlock`

structure that is passed to the callback function `void audioblock(AudioBlock*)`. 

- `input` :: contains sample data from audio input ( if present ). 
- `output` :: expects sample data to be written to by application
- `device_id` :: can be used to distinguish between audio device ( if multiple devices are present )

```c
uint32_t sample_rate
uint8_t  output_channels
uint8_t  input_channels
uint16_t block_size
float**  output
float**  input
uint8_t  device_id
```

## Example `AudioCodec`

```c
{% include_relative code/AudioCodec.ino %}
```

also see [README](https://github.com/Klangstrom/klangstrom-arduino/tree/main/libraries/Klangstrom/examples/basic/AudioCodec) for additional information.

<!-- @TODO rather align with `README.md` {% include_relative code/AudioCodec--README.md %} -->
