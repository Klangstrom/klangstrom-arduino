---
layout: libdoc
title: Key
permalink: /key/
index: 17
---

```c
void key_event(const Key* key)

Key* key_create(uint8_t device_type)
void key_delete(Key* key)
```

## `Key`

```c
uint8_t device_type
bool    pressed
...
```

## Example `Key`

```cpp
{% include_relative code/Key.ino %}
```
