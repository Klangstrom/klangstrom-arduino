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

static constexpr uint32_t WAV_ALL_SAMPLES = 0xFFFFFFFF;

bool         wav_load_header(const std::string& filename);
uint32_t     wav_load_sample_frames(float* buffer, uint32_t num_frames);
uint32_t     wav_num_sample_frames();
wav_reader_t wav_header();
bool         wav_is_open();
bool         wav_looping(bool loop);
void         wav_close();
