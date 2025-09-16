---
layout: page
title: Technical Specifications
abstract: details on the technical details of the board design
permalink: /tech-specs/
index: 3
---

KLST_PANDA is a development based on a STM32H723 Arm® Cortex®-M7 microcontroller (MCU), with 550MHz, 564KB RAM, 1024KB Flash, a Floating-Point Unit (FPU), and an additional 16MB of external memory.

![KLST_PANDA--schematics--peripherals]({{ site.baseurl }}{% link assets/KLST_PANDA--schematics--peripherals.png %})

- ① :: mechanical key ( Cherry MX ) ( left )
- ② :: rotary encoder ( push button, 24 pulses, no dents, 6mm D-shaft ) ( left `00` )
- ③ :: MEMS microphone ( left )
- ④ :: 4.3" TFT display ( 480×272px, 24Bit colors ) and capacitive touch surface
- ⑤ :: on/off switch
- ⑥ :: MEMS microphone ( right )
- ⑦ :: rotary encoder ( push button, 24 pulses, no dents, 6mm D-shaft ) ( right `01` )
- ⑧ :: mechanical key ( Cherry MX ) ( right )
- ⑨ :: power LED ( white )
- ⑩ :: stand-by LED ( white ) + charge LED ( yellow )
- ⑪ :: GPIO port ( 34-pin IDC connector )
- ⑫ :: SDCard reader
- ⑬ :: mounting hole ( 4mm, M4 )
- ⑭ :: line out
- ⑮ :: line in
- ⑯ :: headphones + mic
- ⑰ :: microphone in
- ⑱ :: USB-C device + charge connector
- ⑲ :: programmer interface ( TC2070 )
- ⑳ :: USB-C host connector
- ㉑ :: MIDI out ( analog )
- ㉒ :: MIDI in ( analog )
- ㉓ :: DAC (0.0V–3.3V)
- ㉔ :: ADC (0.0V–3.3V)
- ㉕ :: IDC port ( 6-pin IDC connector ) ( right `01` )
- ㉖ :: rechargeable battery
- ㉗ :: reset button (RST)
- ㉘ :: boot button (BOOT)
- ㉙ :: programmer interface ( STD14 )
- ㉚ :: programmer button (PRG)
- ㉛ :: IDC port ( 6-pin IDC connector ) ( left `00` )

<!--
<ul class="post-list">
    {% assign items = site.manual | sort: 'index' %}
    {% for page in items %}
    <li>
        <a href="{{ page.url | relative_url }}">{{ page.title }}</a>
    </li>
    {% endfor %}
</ul>
-->