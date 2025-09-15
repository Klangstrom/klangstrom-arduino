---
layout: libdoc
title: AudioCodec
permalink: /audiocodec/
index: 4
---

```cpp
AudioDevice* audiodevice_init_audiocodec(AudioInfo* audioinfo);
void         audiodevice_deinit(AudioDevice* audiodevice);
void         audiodevice_resume(AudioDevice* audiodevice);
void         audiodevice_pause(AudioDevice* audiodevice);
void         audiodevice_setup_device(AudioDevice* audiodevice);
AudioDevice* audiodevice_create_from_audioinfo(AudioInfo* audioinfo);
```

```cpp
{% include_relative code/AudioCodec.ino %}
```
