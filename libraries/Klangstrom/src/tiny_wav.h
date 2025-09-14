// /*
//   tiny_wav.h — Minimal, dependency‑free WAV parser (C99)
//   --------------------------------------------------------------------------
//   Goals
//   - No mallocs, no libc I/O required (user supplies read/seek callbacks)
//   - Portable: works on MCUs (e.g., STM32) and desktop
//   - Handles the common cases cleanly:
//       * PCM (format code 1): 8/16/24/32‑bit, N channels
//       * IEEE float (format code 3): 32‑bit float, N channels
//   - Skips unknown chunks and respects even‑byte padding
//   - No unaligned memory access (safe for Cortex‑M0/M3/etc.)

//   Non‑goals (not supported in this tiny header)
//   - Compressed formats (e.g., IMA ADPCM, µ‑law, ALaw)
//   - 64‑bit RF64
//   - Cue/loop/sample metadata beyond basic parsing

//   License: Public Domain / Unlicense. Do whatever you want.

//   Usage (example):
//   --------------------------------------------------------------------------
//     // Provide read/seek over your storage (FILE*, flash, SD card, etc.)
//     size_t my_read(void* user, void* dst, size_t bytes);
//     bool   my_seek(void* user, uint32_t offset_from_start);

//     wav_reader_t wr;
//     if (!wav_open(&wr, my_read, my_seek, my_user_ptr)) { /* handle error */ }

//     // Inspect format
//     printf("%u Hz, %u ch, %u bits, fmt=%u\n", wr.sample_rate, wr.num_channels,
//            wr.bits_per_sample, wr.audio_format);

//     // Read as interleaved frames (clamped/converted to int16 if desired)
//     int16_t buffer[256 * 2]; // 256 frames, up to 2 ch
//     uint32_t got = wav_read_i16(&wr, buffer, 256);

//     // Or read raw bytes from the data chunk
//     // uint32_t n = wav_read_bytes(&wr, dst, max_bytes);

//   Notes
//   --------------------------------------------------------------------------
//   - All multi‑byte values in WAV are little‑endian. Helpers below decode safely.
//   - For streaming, you may call wav_seek_data_start(&wr) once and then read
//     progressively; the struct tracks current position and remaining bytes.
//   - If bits_per_sample==8 (unsigned), wav_read_i16() recenters to signed.
//   - For 24‑bit PCM, wav_read_i16() does simple >>8 truncation; adjust as needed.
// */

#ifndef TINY_WAV_H_
#define TINY_WAV_H_

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// ---- User‑provided I/O ----------------------------------------------------

typedef size_t (*wav_read_cb)(void* user, void* dst, size_t bytes);
// Seek to absolute offset from start of file/stream (0 = beginning)
typedef bool   (*wav_seek_cb)(void* user, uint32_t abs_offset);

// ---- Public reader state --------------------------------------------------

typedef struct {
  // callbacks
  wav_read_cb read;
  wav_seek_cb seek;
  void*       user;

  // parsed fmt
  uint16_t    audio_format;     // 1=PCM, 3=IEEE float
  uint16_t    num_channels;     // e.g., 1,2,...
  uint32_t    sample_rate;      // Hz
  uint16_t    bits_per_sample;  // 8/16/24/32
  uint32_t    bytes_per_frame;  // block align

  // data chunk
  uint32_t    data_offset;      // absolute offset of first data byte
  uint32_t    data_size;        // bytes in data chunk

  // cursor
  uint32_t    cur_abs;          // absolute offset where next read occurs
} wav_reader_t;

// ---- Internal helpers (LE decoding, safe reads) --------------------------

static inline uint16_t wav_u16le(const uint8_t b[2]) {
  return (uint16_t)(b[0] | ((uint16_t)b[1] << 8));
}
static inline uint32_t wav_u32le(const uint8_t b[4]) {
  return (uint32_t)b[0] | ((uint32_t)b[1] << 8) | ((uint32_t)b[2] << 16) | ((uint32_t)b[3] << 24);
}

static bool wav_read_exact(wav_reader_t* w, void* dst, uint32_t n) {
  uint8_t* p = (uint8_t*)dst;
  uint32_t total = 0;
  while (total < n) {
    size_t got = w->read(w->user, p + total, (size_t)(n - total));
    if (got == 0) return false;
    total += (uint32_t)got;
    w->cur_abs += (uint32_t)got;
  }
  return true;
}

static bool wav_skip(wav_reader_t* w, uint32_t n) {
  // Prefer seek if available; fall back to buffered reads if not
  if (w->seek) {
    return w->seek(w->user, w->cur_abs + n) ? (w->cur_abs += n, true) : false;
  } else {
    uint8_t tmp[32];
    while (n) {
      uint32_t chunk = n > sizeof(tmp) ? (uint32_t)sizeof(tmp) : n;
      if (!wav_read_exact(w, tmp, chunk)) return false;
      n -= chunk;
    }
    return true;
  }
}

// ---- Opening / parsing ----------------------------------------------------

static bool wav_parse_fmt_chunk(wav_reader_t* w, uint32_t fmt_size, uint32_t chunk_start_after_idsize) {
  // We will read at most the common 16 bytes (PCM) + 2 (cbSize) + 2 (valid bits) + 4 (channel mask) + 16 (GUID)
  // but only require the core 16 bytes.
  uint8_t hdr[24];
  if (fmt_size < 16) return false;
  if (!wav_read_exact(w, hdr, 16)) return false;
  w->audio_format   = wav_u16le(&hdr[0]);
  w->num_channels   = wav_u16le(&hdr[2]);
  w->sample_rate    = wav_u32le(&hdr[4]);
  /* uint32_t byte_rate = wav_u32le(&hdr[8]); */
  w->bytes_per_frame= wav_u16le(&hdr[12]); // block align
  w->bits_per_sample= wav_u16le(&hdr[14]);

  // Skip any remaining bytes in fmt chunk (including extensible params)
  uint32_t remain = fmt_size - 16;
  if (remain) {
    if (!wav_skip(w, remain)) return false;
  }
  (void)chunk_start_after_idsize; // not used; kept for clarity
  return true;
}

static bool wav_find_chunks(wav_reader_t* w) {
  // Expect RIFF header
  uint8_t riff[12];
  if (!wav_read_exact(w, riff, 12)) return false;
  if (riff[0] != 'R' || riff[1] != 'I' || riff[2] != 'F' || riff[3] != 'F') return false;
  /* uint32_t riff_size = wav_u32le(&riff[4]); */
  if (riff[8] != 'W' || riff[9] != 'A' || riff[10] != 'V' || riff[11] != 'E') return false;

  bool have_fmt = false, have_data = false;
  w->data_offset = 0; w->data_size = 0;

  // Iterate chunks until we find both fmt and data
  for (;;) {
    uint8_t ckhdr[8];
    if (!wav_read_exact(w, ckhdr, 8)) break; // EOF before chunks
    uint32_t size = wav_u32le(&ckhdr[4]);
    uint32_t chunk_start_after_idsize = w->cur_abs; // after the 8 bytes header

    // IDs are 4 ASCII bytes
    if (ckhdr[0]=='f' && ckhdr[1]=='m' && ckhdr[2]=='t' && ckhdr[3]==' ') {
      if (!wav_parse_fmt_chunk(w, size, chunk_start_after_idsize)) return false;
      have_fmt = true;
    } else if (ckhdr[0]=='d' && ckhdr[1]=='a' && ckhdr[2]=='t' && ckhdr[3]=='a') {
      w->data_offset = w->cur_abs; // current position is start of data
      w->data_size   = size;
      // Move cursor to end of data for further scanning (but we can early‑exit if have fmt)
      if (!wav_skip(w, size + (size & 1))) return false; // include pad
      have_data = true;
    } else {
      // Unknown chunk: skip its payload + pad byte if size is odd
      if (!wav_skip(w, size + (size & 1))) return false;
    }

    if (have_fmt && have_data) return true;
  }
  return have_fmt && have_data;
}

static bool wav_seek_abs(wav_reader_t* w, uint32_t abs) {
  if (!w->seek) return false;
  if (!w->seek(w->user, abs)) return false;
  w->cur_abs = abs;
  return true;
}

// Public: open and parse the WAV container
static bool wav_open(wav_reader_t* w, wav_read_cb r, wav_seek_cb s, void* user) {
  if (!w || !r) return false;
  w->read = r; w->seek = s; w->user = user; w->cur_abs = 0;
  w->audio_format = 0; w->num_channels = 0; w->sample_rate = 0; w->bits_per_sample = 0; w->bytes_per_frame = 0;
  w->data_offset = 0; w->data_size = 0;

  if (!wav_find_chunks(w)) return false;

  // Clamp/sanity checks
  if (!(w->audio_format==1 || w->audio_format==3)) return false; // PCM or IEEE float
  if (w->num_channels==0 || w->num_channels>8) return false;
  if (!(w->bits_per_sample==8 || w->bits_per_sample==16 || w->bits_per_sample==24 || w->bits_per_sample==32)) return false;
  if (w->bytes_per_frame == 0) {
    // compute from bits_per_sample*num_channels/8
    uint32_t bpf = ((uint32_t)w->bits_per_sample * (uint32_t)w->num_channels) >> 3;
    w->bytes_per_frame = (uint16_t)bpf;
  }

  // Position at start of data for reading
  if (w->seek) {
    if (!wav_seek_abs(w, w->data_offset)) return false;
  } else {
    // If no seek, we already passed it during parsing; not ideal for stream‑only
    // inputs. In such cases, prefer calling wav_seek_data_start() after open.
  }
  return true;
}

// Rewind to the start of the data chunk
static bool wav_seek_data_start(wav_reader_t* w) {
  if (!w) return false;
  if (!w->seek) return false;
  return wav_seek_abs(w, w->data_offset);
}

// Remaining bytes of audio payload
static uint32_t wav_bytes_remaining(const wav_reader_t* w) {
  if (w->cur_abs < w->data_offset) return w->data_size;
  uint32_t consumed = (w->cur_abs - w->data_offset);
  return consumed >= w->data_size ? 0u : (w->data_size - consumed);
}

// Read raw audio bytes (no format conversion). Returns bytes read.
static uint32_t wav_read_bytes(wav_reader_t* w, void* dst, uint32_t max_bytes) {
  uint32_t remain = wav_bytes_remaining(w);
  if (remain == 0) return 0;
  if (max_bytes > remain) max_bytes = remain;
  if (!wav_read_exact(w, dst, max_bytes)) return 0;
  return max_bytes;
}

// Convenience: read N frames and convert to int16 interleaved.
// Returns number of frames produced.
static uint32_t wav_read_i16(wav_reader_t* w, int16_t* dst, uint32_t max_frames) {
  uint32_t bpf = w->bytes_per_frame;
  if (bpf == 0) return 0;
  uint32_t avail_frames = wav_bytes_remaining(w) / bpf;
  if (max_frames > avail_frames) max_frames = avail_frames;
  if (max_frames == 0) return 0;

  // Process in small chunks to limit stack usage on MCUs
  uint8_t buf[256];
  uint32_t frames_done = 0;
  const uint16_t ch = w->num_channels;

  while (frames_done < max_frames) {
    uint32_t to_do = max_frames - frames_done;
    uint32_t frames_per_buf = sizeof(buf) / bpf;
    if (to_do > frames_per_buf) to_do = frames_per_buf;
    uint32_t bytes_need = to_do * bpf;
    if (!wav_read_exact(w, buf, bytes_need)) break;

    const uint8_t* p = buf;
    for (uint32_t f = 0; f < to_do; ++f) {
      for (uint16_t c = 0; c < ch; ++c) {
        int16_t out = 0;
        if (w->audio_format == 1) {
          // PCM
          if (w->bits_per_sample == 8) {
            // Unsigned 8‑bit centered at 128
            uint8_t v = *p++;
            out = (int16_t)((int32_t)v - 128) << 8; // map 0..255 -> -32768..32767
          } else if (w->bits_per_sample == 16) {
            uint8_t b0 = *p++; uint8_t b1 = *p++;
            out = (int16_t)(b0 | (b1 << 8));
          } else if (w->bits_per_sample == 24) {
            // 24‑bit little‑endian -> sign‑extend, then >>8
            uint32_t b0 = *p++, b1 = *p++, b2 = *p++;
            int32_t v = (int32_t)((b2 << 24) | (b1 << 16) | (b0 << 8));
            out = (int16_t)(v >> 16); // keep most significant 16 bits
          } else if (w->bits_per_sample == 32) {
            // 32‑bit signed PCM -> clamp to i16
            uint8_t b0 = *p++, b1 = *p++, b2 = *p++, b3 = *p++;
            int32_t v = (int32_t)((uint32_t)b0 | ((uint32_t)b1 << 8) | ((uint32_t)b2 << 16) | ((uint32_t)b3 << 24));
            if (v > 32767) v = 32767; else if (v < -32768) v = -32768;
            out = (int16_t)v;
          }
        } else if (w->audio_format == 3) {
          // IEEE float 32‑bit
          if (w->bits_per_sample != 32) { p += (w->bits_per_sample >> 3); out = 0; }
          else {
            // assemble little‑endian to uint32 then alias to float safely
            uint32_t u = (uint32_t)p[0] | ((uint32_t)p[1] << 8) | ((uint32_t)p[2] << 16) | ((uint32_t)p[3] << 24);
            p += 4;
            union { uint32_t u; float f; } cvt; cvt.u = u;
            float fv = cvt.f;
            if (fv > 1.0f) fv = 1.0f; else if (fv < -1.0f) fv = -1.0f;
            int32_t vi = (int32_t)(fv * 32767.0f);
            out = (int16_t)vi;
          }
        }
        *dst++ = out;
      }
    }
    frames_done += to_do;
  }
  return frames_done;
}

#ifdef __cplusplus
}
#endif

#endif /* TINY_WAV_H_ */

// #include <stdio.h>
// #include <stdlib.h>
// #include "tiny_wav.h"

// // ---- File-backed read/seek wrappers ----
// static size_t file_read(void* user, void* dst, size_t bytes) {
//     FILE* f = (FILE*)user;
//     return fread(dst, 1, bytes, f);
// }

// static bool file_seek(void* user, uint32_t abs_offset) {
//     FILE* f = (FILE*)user;
//     return fseek(f, abs_offset, SEEK_SET) == 0;
// }

// // ---- Example program ----
// int main(int argc, char** argv) {
//     if (argc < 2) {
//         printf("usage: %s input.wav\n", argv[0]);
//         return 1;
//     }

//     FILE* f = fopen(argv[1], "rb");
//     if (!f) {
//         perror("fopen");
//         return 1;
//     }

//     wav_reader_t wr;
//     if (!wav_open(&wr, file_read, file_seek, f)) {
//         printf("not a valid wav file\n");
//         fclose(f);
//         return 1;
//     }

//     printf("Format: %s\n", wr.audio_format == 1 ? "PCM" : "Float");
//     printf("Channels: %u\n", wr.num_channels);
//     printf("Sample rate: %u Hz\n", wr.sample_rate);
//     printf("Bits per sample: %u\n", wr.bits_per_sample);
//     printf("Data bytes: %u\n", wr.data_size);

//     // read 256 frames into a buffer
//     int16_t buffer[256 * 2]; // up to stereo
//     uint32_t frames = wav_read_i16(&wr, buffer, 256);
//     printf("Read %u frames\n", frames);

//     fclose(f);
//     return 0;
// }