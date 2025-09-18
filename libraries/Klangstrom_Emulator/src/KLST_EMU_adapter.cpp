/*
 *  Umfeld
 *
 *  This file is part of the *Umfeld* library (https://github.com/dennisppaul/umfeld).
 *  Copyright (c) 2025 Dennis P Paul.
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, version 3.
 *
 *  This library is distributed in the hope that it will be useful, but
 *  WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "Umfeld.h"
#include "KlangstromEmulator.h"

using namespace umfeld;

void klst_emulator_arguments(const std::vector<std::string>& args) {
    warning("INFO :: library implementation -> 'klst_emulator_arguments(args)'");
    KlangstromEmulator::instance()->arguments(args);
    console("INFO :: arguments: ", args.size());
    for (const auto& s: args) {
        console("  - ", s);
    }
}

void klst_emulator_settings() {
    KlangstromEmulator::instance()->settings(); // calls `audio()` or `size()`
    console("INFO :: sketch path: ", sketchPath());
}

void klst_emulator_setup() {
    console_once("INFO :: library implementation -> 'klst_emulator_setup()'");
    KlangstromEmulator::instance()->setup();
}

void klst_emulator_draw() {
    console_once("INFO :: library implementation -> 'klst_emulator_draw()'");
    KlangstromEmulator::instance()->draw();
}

void klst_emulator_update() {
    console_once("INFO :: library implementation -> 'klst_emulator_update()'");
    KlangstromEmulator::instance()->update();
}

void klst_emulator_audioEvent() {
    if (a == nullptr) {
        return;
    }
    warning_in_function_once("INFO :: library implementation -> 'klst_emulator_audioEvent()'");
    // TODO `audioblock` or `handle_audiodevice`
    // TODO rework this into single float array strcture like `umfeld`:
    // KlangstromEmulator::instance()->audioblock(a->input_buffer, a->output_buffer, a->buffer_size);
}

void klst_emulator_keyPressed() {
    console_once("INFO :: library implementation -> 'klst_emulator_keyPressed()'");
    KlangstromEmulator::instance()->keyPressed();
}

void klst_emulator_keyReleased() {
    console_once("INFO :: library implementation -> 'klst_emulator_keyReleased()'");
    KlangstromEmulator::instance()->keyReleased();
}

/*
- [x] void                       arguments(std::vector<std::string> args) override;
- [x] void                       settings() override;
- [x] void                       setup() override;
- [x] void                       draw() override;
- [x] void                       audioblock(float** input, float** output, int length) override;
- [x] void                       keyPressed() override;
- [x] void                       keyReleased() override;

- [ ] bool                       handle_audiodevice(float** input, float** output, int length, KlangstromEmulatorAudioDevice* device);
- [ ] static KlangstromEmulator* instance();
- [ ] static std::string         get_emulator_name();
- [ ] void                       register_drawable(Drawable* drawable);
- [ ] void                       unregister_drawable(Drawable* drawable);
- [ ] void                       delay_loop(uint32_t ms);
- [ ] void                       set_emulator_speed(float loop_frequency_hz) { task.set_frequency(loop_frequency_hz); }
- [ ] float**                    get_audio_output_buffers() const { return mOutputBuffers; }
- [ ] float**                    get_audio_input_buffers() const { return mInputBuffers; }
- [ ] uint8_t                    register_audio_device(AudioDevice* audiodevice);
- [ ] uint8_t                    unregister_audio_device(AudioDevice* audiodevice);
- [ ] uint8_t                    register_serial_device(SerialDevice* serialdevice);
- [ ] uint8_t                    unregister_serial_device(SerialDevice* serialdevice);
- [ ] void                       register_client(KlangstromEmulatorClient* client) { this->client = client; }
- [ ] int                        getWidth() override;
- [ ] int                        getHeight() override;
 */