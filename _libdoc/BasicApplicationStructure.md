---
layout: libdoc
title: Basic Application Structure
permalink: /basicapplication/
index: 100
---

*Klangstrom* supplies an application structure to facilitate the development of applications. 

*Klangstrom* extends the Arduino *idiom* ( i.e `setup`) + `loop()` ) with sound, music + event related functions ( e.g `audioblock()` + `beat()` ). *Klangstrom* also implements a simple abstraction layer to unify access to peripherals ( e.g `data_receive()` + `data_transmit()` ).

every application should include `Klangstrom.h` at the very top. this ensures that the environemnt is configured correctly.
