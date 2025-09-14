/**
 * this example demonstrates how to use an SD card.
*/

#include "Arduino.h"
#include "System.h"
#include "Console.h"
#include "SDCard.h"

// static const int NO_ERROR              = 0;
// static const int ERROR_FILE_NOT_OPEN   = 1;
// static const int ERROR_WAV_16_BIT_ONLY = 2;
// static const int ERROR_WAV_HEADER      = 3;
// static const int ERROR_MEMORY_ALLOCATION_FAILED = 4;
// static const int READ_BUFFER_SIZE      = 512;

// typedef struct KlangstromWaveHeader {
//     /* RIFF Chunk Descriptor */
//     uint8_t  RIFF[4];    // RIFF Header Magic header
//     uint32_t ChunkSize;  // RIFF Chunk Size
//     uint8_t  WAVE[4];    // WAVE Header
//     /* "fmt" sub-chunk */
//     uint8_t  fmt[4];              // FMT header
//     uint32_t Subchunk1Size;       // Size of the fmt chunk
//     uint16_t AudioFormat;         // Audio format 1=PCM,6=mulaw,7=alaw,     257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
//     uint16_t NumOfChan;           // Number of channels 1=Mono 2=Sterio
//     uint32_t SamplesPerSec;       // Sampling Frequency in Hz
//     uint32_t bytesPerSec;         // bytes per second
//     uint16_t bytePerSampleFrame;  // 2=16-bit mono, 4=16-bit stereo
//     uint16_t bitsPerSample;       // Number of bits per sample
//     /* "data" sub-chunk */
//     uint8_t  Subchunk2ID[4];  // "data"  string
//     uint32_t Subchunk2Size;   // Sampled data length
// } WaveHeader_t;

// class KlangstromWaveFile {
// public:
//     static const uint8_t  CHANNEL_LEFT              = 0;
//     static const uint8_t  CHANNEL_RIGHT             = 1;
//     static const uint16_t AUDIO_FORMAT_PCM          = 1;
//     static const uint16_t AUDIO_FORMAT_FLOAT        = 3;
//     static const uint16_t AUDIO_FORMAT_MULAW        = 6;
//     static const uint16_t AUDIO_FORMAT_ALAW         = 7;
//     static const uint16_t AUDIO_FORMAT_IBM_MULAW    = 257;
//     static const uint16_t AUDIO_FORMAT_ADPCM        = 259;
//     static const uint16_t BLOCK_ALIGN_16_BIT_MONO   = 2;
//     static const uint16_t BLOCK_ALIGN_16_BIT_STEREO = 4;

//     WaveHeader_t* header            = nullptr;
//     uint8_t*      sample_data       = nullptr;
//     uint32_t      number_of_samples = 0;

//     int16_t* get_sample_data(const uint8_t pChannel = 0) {
//         return (int16_t*)(sample_data + (number_of_samples * pChannel * (header->bitsPerSample / 8)));
//     }
//     void purge() {
//         if (header != nullptr) {
//             delete header;
//         }
//         if (sample_data != nullptr) {
//             delete[] sample_data;
//         }
//     }
// };

// size_t BSP_read_block(uint8_t* pBuffer, size_t pBytesToRead) {
//     return 0; // number of bytes read
//     // return sdcard_file_read(pBuffer, pBytesToRead);
// }

// uint8_t load_WAV_header(WaveHeader_t *mHeader) {
//     if (!is_open()) {
//         debug_print_error("WAV file not open.\n");
//         return ERROR_FILE_NOT_OPEN;
//     }
//     const uint8_t mHeaderSize = sizeof(WaveHeader_t);
//     size_t        mBytesRead  = BSP_read_block((uint8_t *)mHeader, mHeaderSize);

//     if (mBytesRead <= 0) {
//         debug_print_error("could not read WAV file header.\n");
//         return ERROR_WAV_HEADER;
//     }

//     return NO_ERROR;
// }

// uint8_t load_WAV_data(WaveHeader_t *mHeader) {
//     return NO_ERROR;
// }

// /**
//  * @brief loads the data of WAV file into instance
//  *
//  * @param pWaveFile
//  * @return int error code ( 0 = no error )
//  */
// int load_WAV(KlangstromWaveFile *pWaveFile) {
//     WaveHeader_t *mHeader = new WaveHeader_t();

//     /* read header */
//     uint8_t mLoadHeaderResult = load_WAV_header(mHeader);
//     if (mLoadHeaderResult != NO_ERROR) {
//         return mLoadHeaderResult;
//     }

//     if (mHeader->bitsPerSample != 16) {
//         debug_print_error("only 16bit WAV files are supported.\n");
//         return ERROR_WAV_16_BIT_ONLY;
//     }

//     /* read data */
//     const uint16_t mBytesPerSample = mHeader->bitsPerSample / 8;
//     const uint8_t  mNumChannels    = mHeader->NumOfChan;
//     const uint32_t mNumSamples     = mHeader->Subchunk2Size / mBytesPerSample / mNumChannels;
//     uint8_t        mReadBuffer[READ_BUFFER_SIZE];

//     pWaveFile->header            = mHeader;
//     pWaveFile->sample_data       = new uint8_t[mNumSamples * mNumChannels * mBytesPerSample];
//     pWaveFile->number_of_samples = mNumSamples;

//     if (pWaveFile->sample_data == nullptr) {
//         return ERROR_MEMORY_ALLOCATION_FAILED;
//     }

//     int32_t       mSampleFrameIndex = 0;
//     size_t        mElementsRead     = 0;
//     const uint8_t mElementSize      = mHeader->bytePerSampleFrame;
//     while ((mElementsRead = BSP_read_block(mReadBuffer, READ_BUFFER_SIZE)) > 0) {
//         for (uint32_t i = 0; i < mElementsRead; i += mElementSize) {
//             for (uint8_t j = 0; j < mNumChannels; j++) {
//                 const uint32_t mReadBufferIndex                    = i + mBytesPerSample * j;
//                 const uint32_t mSampleBufferIndex                  = mSampleFrameIndex + mNumSamples * j;
//                 pWaveFile->sample_data[mSampleBufferIndex * 2 + 0] = mReadBuffer[mReadBufferIndex + 0];
//                 pWaveFile->sample_data[mSampleBufferIndex * 2 + 1] = mReadBuffer[mReadBufferIndex + 1];
//             }
//             mSampleFrameIndex++;
//         }
//     }

//     return NO_ERROR;
// }

#include "tiny_wav.h"

static size_t file_read(void* user, void* dst, size_t bytes) {
    return sdcard_file_read(reinterpret_cast<uint8_t*>(dst), bytes);
}

static bool file_seek(void* user, uint32_t abs_offset) {
    if (!sdcard_file_seek(abs_offset)) {
        return false;
    }
    return true;
}

void setup() {
    system_init();
    console_init();
    sdcard_init();

    sdcard_status();

    if (sdcard_detected()) {
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

        // sdcard_mount();
        // std::vector<std::string> files;
        // std::vector<std::string> directories;
        // sdcard_list("", files, directories);
        // for (std::string file: files) {
        //     console_println("    - %s", file);
        //     // if it s a wav file
        //     if (file.substr(file.find_last_of(".") + 1) == "wav") {
        //         console_println("found WAV file: %s", file);
        //         filename = file;    
        //     }
        //     break;
        // }
        if (filename != "") {
            if (sdcard_file_open(filename, FILE_READ_ONLY)) {
                wav_reader_t wav;
                if (wav_open(&wav, file_read, file_seek, nullptr)) {
                    console_println("WAV file opened:");
                    console_println("  Audio format   : %u", wav.audio_format);
                    console_println("  Num channels   : %u", wav.num_channels);
                    console_println("  Sample rate    : %u", wav.sample_rate);
                    console_println("  Bits per sample: %u", wav.bits_per_sample);
                    console_println("  Bytes per frame: %u", wav.bytes_per_frame);
                    console_println("  Data offset    : %u", wav.data_offset);
                    console_println("  Data size      : %u", wav.data_size);
            //         console_println("WAV file opened:");
            //         console_println("  Audio format   : %u", wav.audio_format);
            //         console_println("  Num channels   : %u", wav.num_channels);
            //         console_println("  Sample rate    : %u", wav.sample_rate);
            //         console_println("  Bits per sample: %u", wav.bits_per_sample);
            //         console_println("  Bytes per frame: %u", wav.bytes_per_frame);
            //         console_println("  Data offset    : %u", wav.data_offset);
            //         console_println("  Data size      : %u", wav.data_size);

            //         // read samples
            //         const uint32_t total_frames = wav.data_size / wav.bytes_per_frame;
            //         const uint32_t buffer_frames = 512;
            //         int16_t* buffer = new int16_t[buffer_frames * wav.num_channels];
            //         uint32_t frames_read = 0;
            //         while (frames_read < total_frames) {
            //             uint32_t to_read = buffer_frames;
            //             if (frames_read + to_read > total_frames) {
            //                 to_read = total_frames - frames_read;
            //             }
            //             uint32_t got = wav_read_pcm16(&wav, buffer, to_read);
            //             if (got == 0) break; // EOF or error
            //             // process buffer[0..got*wav.num_channels-1]
            //             frames_read += got;
            //         }
            //         delete[] buffer;
                } else {
                    console_println("error parsing WAV file");
                }
                sdcard_file_close();
            } else {
                console_println("error opening file: %s", filename.c_str());
            }
        } else {
            console_println("no WAV file found on SD card");
        }
        sdcard_unmount();
    }
}

void loop() {
    // if (sdcard_detected()) {
        // sdcard_mount();
        // std::vector<std::string> files;
        // std::vector<std::string> directories;
        // sdcard_list("", files, directories);
        // console_println("SD card detected");
        // console_println("Files      : %i", files.size());
        // for (std::string file: files) {
        //     console_println("             %s", file.c_str());
        // }
    //     console_println("Directories: %i", directories.size());
    //     for (std::string directory: directories) {
    //         console_println("             %s", directory.c_str());
    //     }
    //     console_println("...");
    //     sdcard_unmount();
    // } else {
    //     console_println("SD card not detected");
    // }
    delay(1000);
}
