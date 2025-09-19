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

#include "SDCard.h"
#include "Console.h"

#include "WAVE.h"

static size_t file_read(void* user, void* dst, size_t bytes) {
    return sdcard_file_read(reinterpret_cast<uint8_t*>(dst), bytes);
}

static bool file_seek(void* user, uint32_t abs_offset) {
    if (!sdcard_file_seek(abs_offset)) {
        return false;
    }
    return true;
}

bool WAVE::open(std::string& filename) {
    console_println("open %s", filename.c_str());
    if (sdcard_file_open(filename.c_str(), FILE_READ_ONLY)) {
        console_println("sdcard open %s", filename.c_str());
        if (wav_open(&wav, file_read, file_seek, nullptr)) {
            console_println("WAV file opened:");
            console_println("  Audio format   : %u", wav.audio_format);
            console_println("  Num channels   : %u", wav.num_channels);
            console_println("  Sample rate    : %u", wav.sample_rate);
            console_println("  Bits per sample: %u", wav.bits_per_sample);
            console_println("  Bytes per frame: %u", wav.bytes_per_frame);
            console_println("  Data offset    : %u", wav.data_offset);
            console_println("  Data size      : %u", wav.data_size);
            console_println("  num_frames     : %u", wav_num_frames(&wav));
        } else {
            console_println("error parsing WAV file");
        }
    } else {
        console_println("error opening WAV file");
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
uint32_t WAVE::load_samples(float* buffer, uint32_t num_frames) {
    if (wav.num_channels > 1) {
        console_println("WAVE::load_samples: warning: only mono WAV files are supported, but file has %u channels", wav.num_channels);
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
    if (num_frames == ALL_SAMPLES) {
        num_frames = wav_num_frames(&wav);
    }
    uint32_t _num_frames_read = wav_read_f32(&wav, buffer, num_frames);
    /* loop */
    if (_num_frames_read < num_frames && _is_looping) {
        wav_seek_data_start(&wav);
        _num_frames_read += wav_read_f32(&wav, buffer + _num_frames_read, num_frames - _num_frames_read);
        /* if still not enough samples, the file is probably too short ... should this be commented or handled? */
    }
    return _num_frames_read;
}

void WAVE::close() {
    _is_open = false;
    sdcard_file_close(); // TODO handle result?!?
}

uint32_t WAVE::num_frames() {
    if (!_is_open) {
        return 0;
    }
    return wav_num_frames(&wav);
}

wav_reader_t WAVE::wav;
std::string  WAVE::_filename;
bool         WAVE::_is_open    = false;
bool         WAVE::_is_looping = false;
