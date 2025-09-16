---
layout: libdoc
title: Beat and Timer
permalink: /beatandtimer/
index: 11
---

beat and timers are structures that allow for the creation of reoccuring periodic, time-based events.

## `Beat`

```c
void beat_event(uint8_t beat_id, uint16_t beat_counter)

void init(const uint8_t beat_id)
void set_bpm(const float beats_per_minute)
void pause()
void start()
void resume()
bool is_running()
void reset()
void set_callback(const Callback_2_UI8_UI16& callback)
```

- `beat_event` :: beat event callback invoked on every beat event.
- `set_callback` :: set custom callback to a function with the signature `void my_beat_callback_fucntion(const uint8_t beat_id, const uint16_t beat_counter)`.

## `Timer`

```c
void   timer_event(Timer* timer)

Timer* timer_create(uint8_t timer_id)
void   timer_delete(Timer* timer)
void   timer_resume(Timer* timer)
void   timer_pause(Timer* timer)
void   timer_set_overflow(Timer* timer, uint32_t duration_us)
```

- `timer_event` :: beat event callback invoked on every beat event.
- `timer_create` :: creates a timer. `timer_id` must align with available hardware timer.

## Example `BeatAndTimer`

```c
{% include_relative code/BeatAndTimer.ino %}
```
