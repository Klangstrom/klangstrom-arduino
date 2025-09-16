---
layout: libdoc
title: Encoder
permalink: /encoder/
index: 15
---

rotary encoders invoke events when rotated, pressed or released. KLST_PANDA features two encoders; one left (`00`), one right(`01`) ( see [Technical Specifications](/tech-specs) ):

- ② :: rotary encoder ( push button, 24 pulses, no dents, 6mm D-shaft ) ( left `00` )
- ⑦ :: rotary encoder ( push button, 24 pulses, no dents, 6mm D-shaft ) ( right `01` )

```c
void     encoder_event(Encoder* encoder, uint8_t event)

Encoder* encoder_create(uint8_t device_type);
void     encoder_delete(Encoder* encoder);
void     encoder_start(Encoder* encoder);
void     encoder_stop(Encoder* encoder);
void     encoder_register_listener(Encoder* encoder);
```

## `Encoder`

```c
uint8_t device_type
bool    button_pressed
int32_t rotation
...
```

## Example `Encoder`

```c
{% include_relative code/Encoder.ino %}
```
