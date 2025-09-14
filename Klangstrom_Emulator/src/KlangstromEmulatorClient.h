/*
* Klangstrom
 *
 * This file is part of the *wellen* library (https://github.com/dennisppaul/wellen).
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

#include "OSC.h"
#include "KlangstromEmulatorAudioDevice.h"

struct SerialDevice;

class KlangstromEmulatorClient {
public:
    void receive(const OscMessage& msg);
    bool evaluate_serial_msg(const OscMessage& msg, SerialDevice* device);
    bool update_serial_data(SerialDevice* device, const char* msg_data, const int msg_data_length);
    bool handle_audiodevice(float** input, float** output, int length, KlangstromEmulatorAudioDevice* device);

private:
    void process_device(KlangstromEmulatorAudioDevice* device);
};
