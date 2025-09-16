---
layout: libdoc
title: Console
permalink: /console/
index: 12
---

console is a structure that allows to print information to the programmer debugging serial port ( mostly for debugging ).

```c
void console_printf(format, ...)
void console_print(format, ...)
void console_println(format, ...)
void console_mute(bool mute)
void console_init()
void console_set_color_red()
void console_set_color_green()
void console_reset_color()
void console_clear()
void console_timestamp(bool newline)
void console_system_info()
```

## Example `Console`

```c
{% include_relative code/Console.ino %}
```
