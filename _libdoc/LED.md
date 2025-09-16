---
layout: libdoc
title: LED
permalink: /led/
index: 18
---

KLST_PANDA features two programmable LEDs; one left (`00`), one right(`01`) ( see [Technical Specifications](/tech-specs) ):

```c
void  led_init();
void  led_on(const int id);
void  led_off(const int id);
void  led_toggle(const int id);
void  led_set(const int id, float intensity);
float led_get(const int id);
```

## Example `LED`

```cpp
{% include_relative code/LED.ino %}
```
