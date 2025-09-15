---
layout: page
title: Technical Specifications
permalink: /techspecs/
index: 3
---

KLST_PANDA is a development based on a STM32H723 Arm® Cortex®-M7 microcontroller (MCU), with 550MHz, 564KB RAM, 1024KB Flash, a Floating-Point Unit (FPU), and an additional 16MB of external memory.

![KLST_PANDA--schematics--peripherals]({{ site.baseurl }}{% link assets/KLST_PANDA--schematics--peripherals.png %})

- 01 :: mechanical key ( Cherry MX ) ( left )
- 02 :: rotary encoder ( push button, 24 pulses, no dents, 6mm D-shaft ) ( left )
- 03 :: MEMS microphone ( left )
- 04 :: 4.3" TFT display ( 480×272px, 24Bit colors ) and capacitive touch surface
- 05 :: on/off switch
- 06 :: MEMS microphone ( right )
- 07 :: rotary encoder ( push button, 24 pulses, no dents, 6mm D-shaft ) ( left )
- 08 :: mechanical key ( Cherry MX ) ( right )
- 09 :: power LED ( white )
- 10 :: stand-by LED ( white ) + charge LED ( yellow )
- 11 :: GPIO port ( 34-pin IDC connector )
- 12 :: SDCard reader
- 13 :: mounting hole ( 4mm, M4 )
- 14 :: line out
- 15 :: line in
- 16 :: headphones + mic
- 17 :: microphone in
- 18 :: USB-C device + charge connector
- 19 :: programmer interface ( TC2070 )
- 20 :: USB-C host connector
- 21 :: MIDI out ( analog )
- 22 :: MIDI in ( analog )
- 23 :: DAC (0.0V–3.3V)
- 24 :: ADC (0.0V–3.3V)
- 25 :: IDC port ( 6-pin IDC connector ) ( right )
- 26 :: rechargeable battery
- 27 :: reset button (RST)
- 28 :: boot button (BOOT)
- 29 :: programmer interface ( STD14 )
- 30 :: programmer button (PRG)
- 31 :: IDC port ( 6-pin IDC connector ) ( left )

<ul class="post-list">
    {% assign items = site.manual | sort: 'index' %}
    {% for page in items %}
    <li>
        <a href="{{ page.url | relative_url }}">{{ page.title }}</a>
    </li>
    {% endfor %}
</ul>
