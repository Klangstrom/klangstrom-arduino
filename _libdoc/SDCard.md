---
layout: libdoc
title: SDCard
permalink: /sdcard/
index: 21
---

- @TODO(add demo that streams WAV <- this already exists in Advanced )
- @TODO(add demo that loads WAV)

KLST_PANDA features a micro SDCard reader ( see [Technical Specifications](/tech-specs) ):

- ⑫ :: SDCard reader

```c
bool     sdcard_init();
bool     sdcard_reinit();
bool     sdcard_deinit();
bool     sdcard_detected();
bool     sdcard_status();
bool     sdcard_mount();
bool     sdcard_unmount();
bool     sdcard_format(uint8_t format);
bool     sdcard_list(std::string path, std::vector<std::string>& files, std::vector<std::string>& directories, bool show_hidden_files);
bool     sdcard_file_open(std::string filepath, uint8_t flags);
uint32_t sdcard_file_write(uint8_t* bytes, uint32_t bytes_to_write);
uint32_t sdcard_file_read(uint8_t* bytes, uint32_t bytes_to_read);
bool     sdcard_file_close();
bool     sdcard_file_create(const std::string filename);
bool     sdcard_file_seek(uint32_t position);
bool     sdcard_file_eof();
bool     sdcard_file_attributes(const std::string filename);
```

## Example `SDCard`

```cpp
{% include_relative code/SDCard.ino %}
```
