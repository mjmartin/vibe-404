#pragma once
#include <JuceHeader.h>
#include "PolyBlepOscillator.h"
#include "CurvedADSR.h"
#include "SVFilter.h"
#include "Distortion.h"
#include "../Parameters.h"

class SynthVoice : public juce::MPESynthesiserVoice
{
public:
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numOutputChannels);

    void setParams(const VoiceParams& p, const VoiceModulation& m);

    // MPESynthesiserVoice overrides
    void noteStarted() override;
    void noteStopped(bool allowTailOff) override;
    void notePressureChanged() override {}
    void notePitchbendChanged() override {}
    void noteTimbreChanged() override {}
    void noteKeyStateChanged() override {}
    void renderNextBlock(juce::AudioBuffer<float>& outputBuffer,
                         int startSample, int numSamples) override;

private:
    double baseFrequency = 440.0;

    PolyBlepOscillator osc1, osc2;
    CurvedADSR         ampEnv, filterEnv;
    SVFilter           filter;
    Distortion         dist;

    VoiceParams    params;
    VoiceModulation mod;

    double sampleRate = 44100.0;
};
