---
layout: home
---

{% include KLST--abstract.md %}

## Klangstrom Boards

![KLST_all_boards]({{ site.baseurl }}{% link assets/2024-03-06-KLST_PANDA-middle.jpg %})

please use the [issues tracking system](https://github.com/dennisppaul/klangstrom-arduino/issues) to submit bugs + feature requests.

see [Getting Started]({{ site.baseurl }}{% link _manual/getting-started.md %}) for first steps.

## Operation Manual

<ul class="post-list">
    {% assign items = site.manual | sort: 'index' %}
    {% for page in items %}
    <li>
        <a href="{{ page.url | relative_url }}">{{ page.title }}</a>
    </li>
    {% endfor %}
</ul>

## Klangstrom API Documentation

<ul class="post-list">
    {% assign items = site.libdoc | sort: 'index' %}
    {% for page in items %}
    <li>
        <a href="{{ page.url | relative_url }}">{{ page.title }}</a>
    </li>
    {% endfor %}
</ul>

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


<!-- ![KLST_all_boards]({{ site.baseurl }}{% link assets/KLST_all_boards.jpg %})-->