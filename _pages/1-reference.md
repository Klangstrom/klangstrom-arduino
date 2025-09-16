---
layout: page
title: Reference
permalink: /reference/
---

this reference is organzied around examples which can be found in the *Klangstrom* libraries folder `Klangstrom/examples/basic`.

## By Example

<ul class="post-list">
        {% assign items = site.libdoc | sort: 'index' %}
        {% for page in items %}
            {%- if page.index < 100 -%}
                <li>
                    <a href="{{ page.url | relative_url }}">{{ page.title }}</a>
                </li>
            {%- endif -%}
        {% endfor %}
</ul>

## Environment

<ul class="post-list">
        {% assign items = site.libdoc | sort: 'index' %}
        {% for page in items %}
            {%- if page.index >= 100 -%}
                <li>
                    <a href="{{ page.url | relative_url }}">{{ page.title }}</a>
                </li>
            {%- endif -%}
        {% endfor %}
</ul>

examples can be found in the *Klangstrom* library folder basic example sections:

```sh
Klangstrom/examples
├── advanced
│   └── ...
└── basic
    ├── AudioCodec
    ├── BeatAndTimer
    ├── Console
    ├── DACADC
    ├── Display
    ├── Encoder
    ├── IDC
    ├── Key
    ├── LED
    ├── Microphone
    ├── MIDI
    ├── SDCard
    └── Tasks
```

also see [advanced examples](https://github.com/Klangstrom/klangstrom-arduino/tree/main/libraries/Klangstrom/examples/advanced)

## Utilities+Tools

- `embedded_cli`
- `Tools`