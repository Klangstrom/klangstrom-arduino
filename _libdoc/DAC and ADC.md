---
layout: libdoc
title: DAC and ADC
permalink: /dacadc/
index: 13
---

analog-digital-converter (ADC) and digital-analog-converter (DAC) convert digital values into *analog* voltages and vice versa. ADC and DAC have an operational range of 0.0V–3.3V. both convertes are accessible via *audio jacks* on KLST_PANDA ( see [Technical Specifications](/tech-specs) ):

- ㉓ :: DAC (0.0V–3.3V)
- ㉔ :: ADC (0.0V–3.3V)

```c
void dac_init()
void dac_write(float value) 
void dac_start()
void dac_stop()
void  adc_init()
float adc_read()
```

## Example `DACADC`

```c
{% include_relative code/DACADC.ino %}
```
