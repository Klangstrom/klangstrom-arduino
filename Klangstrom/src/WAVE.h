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

#pragma once

#include <string>

#include "tiny_wav.h"

class WAVE {
public:
    static const uint32_t ALL_SAMPLES = 0xFFFFFFFF;

    static bool     open(std::string& filename);
    static uint32_t load_samples(float* buffer, uint32_t num_frames);
    static void     close();
    static bool     is_open() { return _is_open; }
    static bool     looping(const bool loop) {
        _is_looping = loop;
        return _is_looping;
    }
    static uint32_t num_frames();

private:
    static std::string  _filename;
    static wav_reader_t wav;
    static bool         _is_open;
    static bool         _is_looping;
};