#include "daisy_patch_sm.h"
#include "daisysp.h"

using namespace daisy;
using namespace patch_sm;
using namespace daisysp;

DaisyPatchSM patch;

// Core Modules
Drip         drip;
Svf          filt;
Adsr         env;

// Effects
Wavefolder   wavefolder;
PitchShifter pitchshifter;

void AudioCallback(AudioHandle::InputBuffer  in,
                   AudioHandle::OutputBuffer out,
                   size_t                    size)
{
    patch.ProcessAllControls();

    // Process Gates
    bool triggered = patch.gate_in_1.Trig();
    if(triggered)
    {
        env.Retrigger(false);
    }

    // Process Controls
    env.SetAttackTime(fmap(patch.GetAdcValue(CV_1), 0.001f, 4.f));
    env.SetDecayTime(fmap(patch.GetAdcValue(CV_2), 0.001f, 4.f));
    env.SetSustainLevel(patch.GetAdcValue(CV_3));
    env.SetReleaseTime(fmap(patch.GetAdcValue(CV_4), 0.001f, 4.f));

    filt.SetFreq(fmap(patch.GetAdcValue(CV_5), 20.f, 20000.f, Mapping::LOG));
    filt.SetRes(fmap(patch.GetAdcValue(CV_6), 0.f, 0.95f));

    wavefolder.SetGain(fmap(patch.GetAdcValue(CV_7), 0.f, 10.f));
    wavefolder.SetOffset(fmap(patch.GetAdcValue(CV_8), -0.8f, 0.8f));

    pitchshifter.SetTransposition(fmap(patch.GetAdcValue(ADC_9), -12.f, 12.f));
    pitchshifter.SetFun(patch.GetAdcValue(ADC_10));


    for(size_t i = 0; i < size; i++)
    {
        float env_out = env.Process(patch.gate_in_1.State());
        float sig     = drip.Process(triggered);
        sig *= env_out;

        // Process through filter
        filt.Process(sig);
        sig = filt.Low();
        
        // Process through effects
        sig = wavefolder.Process(sig);
        sig = pitchshifter.Process(sig);

        OUT_L[i] = sig;
        OUT_R[i] = sig;
    }
}

int main(void)
{
    patch.Init();
    float sample_rate = patch.AudioSampleRate();

    drip.Init(sample_rate, 0.1f);
    filt.Init(sample_rate);
    env.Init(sample_rate);
    wavefolder.Init();
    pitchshifter.Init(sample_rate);

    patch.StartAudio(AudioCallback);
    while(1) {}
}