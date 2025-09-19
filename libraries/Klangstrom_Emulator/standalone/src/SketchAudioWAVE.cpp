/**
 * this example demonstrates load and play a WAV file from an SD card.
 */

#include "Arduino.h"
#include "System.h"
#include "Console.h"
#include "AudioDevice.h"
#include "SDCard.h"
#include "WAVE.h"
#include "Key.h"

Key* key_left;

int    sample_buffer_size;
float* sample_buffer;
bool   update_audio_block = false;

void setup() {
    system_init();
    console_init();
    sdcard_init();

    key_left = key_create(KEY_LEFT);

    while (!sdcard_detected()) {
        console_println("SD card not detected");
        delay(1000);
    }
    sdcard_status();

    sdcard_mount();
    std::vector<std::string> files;
    std::vector<std::string> directories;
    sdcard_list("", files, directories);
    console_println("SD card detected");
    console_println("Files      : %i", files.size());
    for (std::string file: files) {
        console_println("             %s", file.c_str());
    }
    std::string filename = "";
    for (std::string file: files) {
        if (file.substr(file.find_last_of(".") + 1) == "WAV") {
            console_println("found WAV file: %s", file.c_str());
            filename = file;
            break;
        }
    }
    console_println("found %s", filename.c_str());
    if (filename != "") {
        WAVE::open(filename);
        console_println("%i samples in WAV file", WAVE::num_frames());
    } else {
        console_println("no WAV file found on SD card");
    }

    if (WAVE::is_open()) {
        console_println("start playing WAV file ...");
    } else {
        console_println("no WAV file opened");
    }

    sample_buffer_size = WAVE::num_frames();
    sample_buffer      = new float[sample_buffer_size];
    WAVE::load_samples(sample_buffer, WAVE::ALL_SAMPLES);
    WAVE::looping(false);

    system_init_audiocodec();
}

void loop() {
    if (update_audio_block) {
        update_audio_block = false;
        if (WAVE::is_open()) {
            //WAVE::load_samples(rows, audio_block_size);
        }
    }
}

uint32_t sample_buffer_counter = 0;

void audioblock(AudioBlock* audio_block) {
    for (int i = 0; i < audio_block->block_size; ++i) {
        float sample = 0.0f;
        if (sample_buffer_counter < sample_buffer_size) {
            sample_buffer_counter++;
            sample = sample_buffer[sample_buffer_counter];
        }
        for (int c = 0; c < audio_block->output_channels; ++c) {
            audio_block->output[c][i] = sample;
        }
    }
    update_audio_block = true;
}

void key_event(const Key* key) {
    if (key->device_id == key_left->device_id) {
        if (key->pressed) {
            sample_buffer_counter = 0;
        }
    }
}