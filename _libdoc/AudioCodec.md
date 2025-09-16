---
layout: libdoc
title: AudioCodec
permalink: /audiocodec/
index: 10
---

```cpp
AudioDevice* audiodevice_init_audiocodec(AudioInfo* audioinfo);
void         audiodevice_deinit(AudioDevice* audiodevice);
void         audiodevice_resume(AudioDevice* audiodevice);
void         audiodevice_pause(AudioDevice* audiodevice);
void         audiodevice_setup_device(AudioDevice* audiodevice);
AudioDevice* audiodevice_create_from_audioinfo(AudioInfo* audioinfo);
```

- `AudioBlock`
- `AudioInfo`
- `AudioDevice`

<!-- @TODO rather align with `README.md` {% include_relative code/AudioCodec--README.md %} -->

```cpp
{% include_relative code/AudioCodec.ino %}
```

also see [README](https://github.com/Klangstrom/klangstrom-arduino/tree/main/libraries/Klangstrom/examples/basic/AudioCodec).
