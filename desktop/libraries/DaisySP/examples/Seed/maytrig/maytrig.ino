// Title: maytrig
// Description: Probabilistically triggers an adenv
// Hardware: Daisy Seed
// Author: Ben Sergentanis

#include "Klangstrom.h"
#include "DaisySP.h"

using namespace daisysp;

size_t num_channels = KLANG_OUTPUT_CHANNELS;
float  sample_rate  = KLANG_AUDIO_RATE;

static AdEnv      env;
static Oscillator osc;
static Maytrig    maytrig;
static Metro      tick;

void audioblock(float** in, float** out) {
    size_t size = KLANG_SAMPLES_PER_AUDIO_BLOCK;
    float  osc_out, env_out;
    for (size_t i = 0; i < size; i++) {
        // When the metro ticks, trigger the envelope to start.
        if (tick.Process()) {
            if (maytrig.Process(.7)) {
                env.Trigger();
                osc.SetFreq(((float)rand() / RAND_MAX) * 800 + 200);
            }
        }

        // Use envelope to control the amplitude of the oscillator.
        env_out = env.Process();
        osc.SetAmp(env_out);
        osc_out = osc.Process();
        for (size_t chn = 0; chn < num_channels; chn++) {
            out[chn][i] = osc_out;
        }
    }
}

void setup() {
    env.Init(sample_rate);
    osc.Init(sample_rate);
    tick.Init(1, sample_rate);

    // set adenv parameters
    env.SetTime(ADENV_SEG_ATTACK, 0.01);
    env.SetTime(ADENV_SEG_DECAY, 0.1);
    env.SetMin(0.0);
    env.SetMax(0.25);
    env.SetCurve(0.5);

    // Set parameters for oscillator
    osc.SetWaveform(osc.WAVE_TRI);
    osc.SetFreq(220);
    osc.SetAmp(0.25);
}

void loop() {}
