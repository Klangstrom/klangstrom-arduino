---
layout: home
---

{% include KLST--abstract.md %}

![KLST_PANDA]({{ site.baseurl }}{% link assets/2024-03-06-KLST_PANDA-middle.jpg %})

## Quickstart Guide

- install [Arduino IDE](https://www.arduino.cc/en/software/#ide)
- install [STM32duino / Arduino_Core_STM32](https://github.com/stm32duino/Arduino_Core_STM32?tab=readme-ov-file#getting-started)
- open console and copy-paste [klangstrom-arduino](https://github.com/Klangstrom/klangstrom-arduino) installer below:

⚠️⚠️⚠️ WIP does not work ATM ⚠️⚠️⚠️
```sh
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Klangstrom/klangstrom-arduino/main/install.sh)"
```

see [Installation](/installation) for detailed installatin instructions.

## Operation Manual

<ul class="post-list">
    {% assign items = site.manual | sort: 'index' %}
    {% for page in items %}
    <li>
        <a href="{{ page.url | relative_url }}">{{ page.title }}</a> :: {{ page.abstract }}
    </li>
    {% endfor %}
</ul>

the project is hosted on GitHub at [Klangstrom](https://github.com/Klangstrom). some repositories require invitation. please use the [issues tracking system](https://github.com/dennisppaul/klangstrom-arduino/issues) to submit bugs + feature requests.

<!-- 
{%- if site.posts.size > 0 -%}
<div class="libdoc-list">
    <h2>Releases</h2>
    <ul class="post-list">
        {%- for post in site.posts -%}
        <li>
            <a class="post-link" href="{{ post.url | relative_url }}">
                    {{ post.title | escape }}
                    {%- assign date_format = site.minima.date_format | default: "%b %-d, %Y" -%}
            </a> 
            ({{ post.date | date: date_format }})
            {%- if site.show_excerpts -%}
                : {{ post.excerpt | strip_newlines | replace: '<p>', ' ' | replace: '</p>', ' ' }}
            {%- endif -%}
        </li>
        {%- endfor -%}
    </ul>
</div>
{%- endif -%}
-->