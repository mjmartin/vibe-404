#include "SynthVoice.h"
#include <cmath>

void SynthVoice::prepareToPlay(double sr, int samplesPerBlock, int /*numOutputChannels*/)
{
    sampleRate = sr;
    osc1.prepare(sr);
    osc2.prepare(sr);
    ampEnv.prepare(sr);
    filterEnv.prepare(sr);

    juce::dsp::ProcessSpec spec { sr, (juce::uint32)samplesPerBlock, 1 };
    filter.prepare(spec);
}

void SynthVoice::setParams(const VoiceParams& p, const VoiceModulation& m)
{
    params = p;
    mod    = m;
}

void SynthVoice::noteStarted()
{
    auto note = getCurrentlyPlayingNote();
    baseFrequency = note.getFrequencyInHertz();

    osc1.reset();
    osc2.reset();
    ampEnv.noteOn();
    filterEnv.noteOn();
}

void SynthVoice::noteStopped(bool allowTailOff)
{
    if (allowTailOff)
    {
        ampEnv.noteOff();
        filterEnv.noteOff();
    }
    else
    {
        clearCurrentNote();
    }
}

void SynthVoice::renderNextBlock(juce::AudioBuffer<float>& outputBuffer,
                                  int startSample, int numSamples)
{
    if (!ampEnv.isActive())
    {
        clearCurrentNote();
        return;
    }

    // Apply envelope ADSR parameters
    ampEnv.setParameters(params.envAttack, params.envDecay,
                         params.envSustain, params.envRelease, params.envSlope);
    filterEnv.setParameters(params.envAttack, params.envDecay,
                            params.envSustain, params.envRelease, params.envSlope);

    // Oscillator shapes
    osc1.setWaveShape(static_cast<WaveShape>(params.osc1Wave));
    osc1.setPulseWidth(params.osc1PW);
    osc2.setWaveShape(static_cast<WaveShape>(params.osc2Wave));
    osc2.setPulseWidth(params.osc2PW);

    // Filter type
    filter.setType(static_cast<FilterType>(params.filterType));

    for (int i = 0; i < numSamples; ++i)
    {
        // Compute OSC1 frequency with octave/semi/fine + LFO pitch mod
        double pitchSemis = static_cast<double>(params.osc1Octave * 12 + params.osc1Semi)
                          + static_cast<double>(params.osc1Fine) / 100.0
                          + static_cast<double>(mod.lfoToPitch);
        double freq1 = baseFrequency * std::pow(2.0, pitchSemis / 12.0);
        osc1.setFrequency(freq1);

        double pitchSemis2 = static_cast<double>(params.osc2Octave * 12 + params.osc2Semi)
                           + static_cast<double>(params.osc2Fine) / 100.0
                           + static_cast<double>(mod.lfoToPitch);
        double freq2 = baseFrequency * std::pow(2.0, pitchSemis2 / 12.0);
        osc2.setFrequency(freq2);

        float s1 = osc1.processSample();

        // Hard sync: osc1 reset triggers osc2 reset
        if (params.osc2Sync && osc1.didReset())
            osc2.reset();

        float s2 = osc2.processSample();

        // Mix
        float mixed = s1 + params.oscMix * (s2 - s1);   // lerp(s1, s2, mix)

        // Ring mod
        if (params.ringMod)
            mixed *= s1;

        // Amplitude envelope
        mixed *= ampEnv.processSample();

        // Filter
        float filterEnvVal = filterEnv.processSample();
        float cutoff = params.filterCutoff
                     + filterEnvVal * params.filterEnv * 10000.f
                     + mod.lfoToCutoff;
        cutoff = juce::jlimit(20.f, 20000.f, cutoff);

        float res = juce::jlimit(0.f, 1.f, params.filterRes + mod.lfoToRes);
        filter.setCutoff(cutoff);
        filter.setResonance(res);
        mixed = filter.processSample(mixed);

        // Distortion
        mixed = dist.process(mixed, params.distDrive, static_cast<DistMode>(params.distMode));

        // Write to both output channels
        for (int ch = 0; ch < outputBuffer.getNumChannels(); ++ch)
            outputBuffer.addSample(ch, startSample + i, mixed);
    }

    if (!ampEnv.isActive())
        clearCurrentNote();
}
