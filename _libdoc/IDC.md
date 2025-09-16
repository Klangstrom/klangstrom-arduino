---
layout: libdoc
title: IDC ( Inter Device Connection )
permalink: /idc/
index: 16
---

*IDC* stands for *Inter-Device Connection* and can be used to send and receive serial data between boards.

KLST_PANDA features two such connectors; one left (`00`), one right(`01`) ( see [Technical Specifications](/tech-specs) ):

- ㉕ :: IDC port ( 6-pin IDC connector ) ( right `01` )
- ㉛ :: IDC port ( 6-pin IDC connector ) ( left `00` )

( *IDC* incidentally also uses a *Insulation-Displacement Contact* )

## `SerialDevice`

```c
void          serial_event(SerialDevice* serial_device)

SerialDevice* serialdevice_create(uint8_t device_type, uint32_t buffer_size, uint32_t baud_rate)
void          serialdevice_delete(SerialDevice* serialdevice)
void          serialdevice_send(const SerialDevice* serialdevice, const uint8_t* data, uint16_t length)
```

## Example `IDC`

```cpp
{% include_relative code/IDC.ino %}
```
