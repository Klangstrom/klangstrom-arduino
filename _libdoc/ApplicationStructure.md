---
layout: libdoc
title: Application Structure
permalink: /application/
index: 100
---

*Klangstrom* supplies an application structure to facilitate the development of applications. 

*Klangstrom* extends the Arduino *idiom* ( i.e `setup`) + `loop()` ) with sound, music + event related functions ( e.g `audioblock()` + `beat()` ).

```c
#include "Arduino.h"
#include "Klangstrom.h"

void setup() {}

void loop() {}
```

every application should include `Klangstrom.h` at the very top. this ensures that the environemnt is configured correctly.
