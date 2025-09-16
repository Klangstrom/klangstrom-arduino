---
layout: libdoc
title: Tasks
permalink: /tasks/
index: 22
---

tasks can be used to structure an application. `TaskScheduler` features *one time* tasks and prioritized task as well as repeated tasks.

```c
void schedule_priority_task(TaskCallbackType callback)
void remove_priority_task(TaskCallbackType callback)
void schedule_task(TaskCallbackType callback)
void remove_task(TaskCallbackType callback)
void schedule_repeated_task(TaskCallbackType callback)
void remove_repeated_task(TaskCallbackType callback)
bool process()
```

## Example `Tasks`

```c
{% include_relative code/Tasks.ino %}
```
