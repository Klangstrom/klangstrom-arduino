/**
 * this example demonstrates load and play a WAV file from an SD card.
 */

#include "Arduino.h"
#include "System.h"
#include "Console.h"
#include "AudioDevice.h"
#include "SDCard.h"
#include "WAVE.h"

const int sample_buffer_size = 49396;
float sample_buffer[sample_buffer_size];
bool update_audio_block = false;

void setup() {
    system_init();
    console_init();
    sdcard_init();

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
    std::string filename ="";
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
        console_println("%i samples in WAV file", WAVE::num_samples());
    } else {
        console_println("no WAV file found on SD card");
    }

    if (WAVE::is_open()) {
        console_println("start playing WAV file ...");
    } else {
        console_println("no WAV file opened");
    }

    sdcard_file_read(reinterpret_cast<uint8_t*>(sample_buffer), 49396);
    // WAVE::load_samples(sample_buffer, 512);
    // WAVE::looping(true);
    
    system_init_audiocodec();
}

uint32_t counter = 0;

void loop() {
    if (update_audio_block) {
        counter++;
        if (counter % 512 == 0) {
            console_println("audio blocks played: %i", counter / 512);
        }
        update_audio_block = false;
        if (WAVE::is_open()) {
            //WAVE::load_samples(rows, audio_block_size);
        }
    }
}

float random_f() {
    return random() / (float)RAND_MAX;
}

uint32_t sample_buffer_counter = 0;

void audioblock(AudioBlock* audio_block) {
    for (int i = 0; i < audio_block->block_size; ++i) {
        for (int c = 0; c < audio_block->output_channels; ++c) {
            sample_buffer_counter++;
            sample_buffer_counter %= sample_buffer_size;
            audio_block->output[c][i] = sample_buffer[sample_buffer_counter];
            // audio_block->output[c][i] = random_f() * 2.0 - 1.0;
        }
    }
    update_audio_block = true;
}
