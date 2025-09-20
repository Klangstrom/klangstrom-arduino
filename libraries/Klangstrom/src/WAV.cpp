/*
* Klangstrom
*
* This file is part of the *Klangstrom* library (https://github.com/dennisppaul/klangstrom-libraries).
* Copyright (c) 2025 Dennis P Paul.
*
* This library is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, version 3.
*
* This library is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
* General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include "KlangstromDefines.h"
#include "SDCard.h"
#include "WAV.h"

#define WAV_PRINT_DEBUG FALSE
#if WAV_PRINT_DEBUG
#include "Console.h"
#define WAV_CONSOLE_PRINTLN(...) console_println(__VA_ARGS__)
#else
#define WAV_CONSOLE_PRINTLN(...)
#endif

static std::string  _filename = "";
static wav_reader_t _wav_reader;
static bool         _is_open    = false;
static bool         _is_looping = false;

static size_t _file_read(void* user, void* dst, size_t bytes) {
    return sdcard_file_read(static_cast<uint8_t*>(dst), bytes);
}

static bool _file_seek(void* user, uint32_t abs_offset) {
    if (!sdcard_file_seek(abs_offset)) {
        return false;
    }
    return true;
}

bool wav_is_open() { return _is_open; }

bool wav_looping(const bool loop) {
    _is_looping = loop;
    return _is_looping;
}

bool wav_load_header(const std::string& filename) {
    WAV_CONSOLE_PRINTLN("open %s", filename.c_str());
    if (sdcard_file_open(filename.c_str(), FILE_READ_ONLY)) {
        WAV_CONSOLE_PRINTLN("sdcard open %s", filename.c_str());
        if (wav_open(&_wav_reader, _file_read, _file_seek, nullptr)) {
            WAV_CONSOLE_PRINTLN("WAV file opened:");
            WAV_CONSOLE_PRINTLN("  Audio format   : %u", _wav_reader.audio_format);
            WAV_CONSOLE_PRINTLN("  Num channels   : %u", _wav_reader.num_channels);
            WAV_CONSOLE_PRINTLN("  Sample rate    : %u", _wav_reader.sample_rate);
            WAV_CONSOLE_PRINTLN("  Bits per sample: %u", _wav_reader.bits_per_sample);
            WAV_CONSOLE_PRINTLN("  Bytes per frame: %u", _wav_reader.bytes_per_frame);
            WAV_CONSOLE_PRINTLN("  Data offset    : %u", _wav_reader.data_offset);
            WAV_CONSOLE_PRINTLN("  Data size      : %u", _wav_reader.data_size);
            WAV_CONSOLE_PRINTLN("  num_frames     : %u", wav_num_frames(&_wav_reader));
        } else {
            WAV_CONSOLE_PRINTLN("error parsing WAV file");
        }
    } else {
        WAV_CONSOLE_PRINTLN("error opening WAV file");
        _filename = "";
        _is_open  = false;
        return false;
    }
    _is_open  = true;
    _filename = filename;
    return true;
}

/*
 * loads samples into buffer. buffer must be large enough to hold num_samples. if looping is enabled
 * and end of file is reached, it will continue reading from the beginning.
 * @returns number of samples read
 */
uint32_t wav_load_sample_frames(float* buffer, uint32_t num_frames) {
    if (_wav_reader.num_channels > 1) {
        WAV_CONSOLE_PRINTLN("load_samples: warning: only mono WAV files are supported, but file has %u channels", _wav_reader.num_channels);
    }
    if (!_is_open) {
        return 0;
    }
    if (num_frames == 0) {
        return 0;
    }
    if (buffer == nullptr) {
        return 0;
    }
    if (num_frames == WAV_ALL_SAMPLES) {
        num_frames = wav_num_frames(&_wav_reader);
    }
    uint32_t _num_frames_read = wav_read_f32(&_wav_reader, buffer, num_frames);
    /* loop */
    if (_num_frames_read < num_frames && _is_looping) {
        wav_seek_data_start(&_wav_reader);
        _num_frames_read += wav_read_f32(&_wav_reader, buffer + _num_frames_read, num_frames - _num_frames_read);
        /* if still not enough samples, the file is probably too short ... should this be commented or handled? */
    }
    return _num_frames_read;
}

void wav_close() {
    _is_open = false;
    sdcard_file_close(); // TODO handle result?!?
}

uint32_t wav_num_sample_frames() {
    if (!_is_open) {
        return 0;
    }
    return wav_num_frames(&_wav_reader);
}

wav_reader_t wav_header() {
    if (!_is_open) {
        WAV_CONSOLE_PRINTLN("WAV file not open");
    }
    return _wav_reader;
}
