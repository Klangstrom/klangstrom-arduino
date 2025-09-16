---
layout: libdoc
title: Microphone
permalink: /microphone/
index: 19
---

KLST_PANDA features two on-board MEMS microphones; one left, one right ( see [Technical Specifications](/tech-specs) ):

- ③ :: MEMS microphone ( left )
- ⑥ :: MEMS microphone ( right )

```c
void audioblock(AudioBlock* audio_block)

Microphone* microphone_init(AudioInfo* audio_info)
void        microphone_deinit(Microphone* microphone)
void        microphone_start(Microphone* microphone)
void        microphone_stop(Microphone* microphone)
```

## Example `Microphone`

```cpp
{% include_relative code/Microphone.ino %}
```
