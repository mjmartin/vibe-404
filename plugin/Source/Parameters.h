#pragma once
#include <JuceHeader.h>

namespace ParamID
{
    // Oscillator 1
    inline constexpr const char* osc1Wave    = "osc1_wave";
    inline constexpr const char* osc1Octave  = "osc1_octave";
    inline constexpr const char* osc1Semi    = "osc1_semi";
    inline constexpr const char* osc1Fine    = "osc1_fine";
    inline constexpr const char* osc1PW      = "osc1_pw";

    // Oscillator 2
    inline constexpr const char* osc2Wave    = "osc2_wave";
    inline constexpr const char* osc2Octave  = "osc2_octave";
    inline constexpr const char* osc2Semi    = "osc2_semi";
    inline constexpr const char* osc2Fine    = "osc2_fine";
    inline constexpr const char* osc2PW      = "osc2_pw";
    inline constexpr const char* osc2Sync    = "osc2_sync";

    // Mix
    inline constexpr const char* oscMix      = "osc_mix";
    inline constexpr const char* ringMod     = "ring_mod";

    // Envelope
    inline constexpr const char* envAttack   = "env_attack";
    inline constexpr const char* envDecay    = "env_decay";
    inline constexpr const char* envSustain  = "env_sustain";
    inline constexpr const char* envSlope    = "env_slope";
    inline constexpr const char* envRelease  = "env_release";

    // Filter
    inline constexpr const char* filterType    = "filter_type";
    inline constexpr const char* filterCutoff  = "filter_cutoff";
    inline constexpr const char* filterRes     = "filter_res";
    inline constexpr const char* filterEnv     = "filter_env";

    // LFO
    inline constexpr const char* lfoWave      = "lfo_wave";
    inline constexpr const char* lfoRate      = "lfo_rate";
    inline constexpr const char* lfoToPitch   = "lfo_to_pitch";
    inline constexpr const char* lfoToCutoff  = "lfo_to_cutoff";
    inline constexpr const char* lfoToRes     = "lfo_to_res";
    inline constexpr const char* lfoToPW      = "lfo_to_pw";

    // Distortion
    inline constexpr const char* distMode     = "dist_mode";
    inline constexpr const char* distDrive    = "dist_drive";
}

namespace Parameters
{
    inline juce::AudioProcessorValueTreeState::ParameterLayout createLayout()
    {
        using namespace juce;
        std::vector<std::unique_ptr<RangedAudioParameter>> params;

        auto waveChoices = StringArray { "Sine", "Tri", "Saw", "RevSaw", "Square", "Noise" };

        // OSC 1
        params.push_back(std::make_unique<AudioParameterChoice>(ParamID::osc1Wave, "OSC1 Wave", waveChoices, 2));
        params.push_back(std::make_unique<AudioParameterInt>(ParamID::osc1Octave, "OSC1 Octave", -2, 2, 0));
        params.push_back(std::make_unique<AudioParameterInt>(ParamID::osc1Semi, "OSC1 Semi", -12, 12, 0));
        params.push_back(std::make_unique<AudioParameterFloat>(ParamID::osc1Fine, "OSC1 Fine",
            NormalisableRange<float>(-100.f, 100.f, 0.1f), 0.f));
        params.push_back(std::make_unique<AudioParameterFloat>(ParamID::osc1PW, "OSC1 PW",
            NormalisableRange<float>(0.01f, 0.99f, 0.01f), 0.5f));

        // OSC 2
        params.push_back(std::make_unique<AudioParameterChoice>(ParamID::osc2Wave, "OSC2 Wave", waveChoices, 0));
        params.push_back(std::make_unique<AudioParameterInt>(ParamID::osc2Octave, "OSC2 Octave", -2, 2, 0));
        params.push_back(std::make_unique<AudioParameterInt>(ParamID::osc2Semi, "OSC2 Semi", -12, 12, 0));
        params.push_back(std::make_unique<AudioParameterFloat>(ParamID::osc2Fine, "OSC2 Fine",
            NormalisableRange<float>(-100.f, 100.f, 0.1f), 0.f));
        params.push_back(std::make_unique<AudioParameterFloat>(ParamID::osc2PW, "OSC2 PW",
            NormalisableRange<float>(0.01f, 0.99f, 0.01f), 0.5f));
        params.push_back(std::make_unique<AudioParameterBool>(ParamID::osc2Sync, "OSC2 Sync", false));

        // Mix
        params.push_back(std::make_unique<AudioParameterFloat>(ParamID::oscMix, "OSC Mix",
            NormalisableRange<float>(0.f, 1.f, 0.01f), 0.5f));
        params.push_back(std::make_unique<AudioParameterBool>(ParamID::ringMod, "Ring Mod", false));

        // Envelope (logarithmic time ranges)
        auto timeRange = NormalisableRange<float>(0.001f, 10.f);
        timeRange.setSkewForCentre(0.3f);
        params.push_back(std::make_unique<AudioParameterFloat>(ParamID::envAttack,  "Attack",  timeRange, 0.01f));
        params.push_back(std::make_unique<AudioParameterFloat>(ParamID::envDecay,   "Decay",   timeRange, 0.1f));
        params.push_back(std::make_unique<AudioParameterFloat>(ParamID::envSustain, "Sustain",
            NormalisableRange<float>(0.f, 1.f, 0.01f), 0.7f));
        params.push_back(std::make_unique<AudioParameterFloat>(ParamID::envSlope, "Slope",
            NormalisableRange<float>(0.f, 1.f, 0.01f), 0.5f));
        params.push_back(std::make_unique<AudioParameterFloat>(ParamID::envRelease, "Release", timeRange, 0.2f));

        // Filter
        auto filterChoices = StringArray { "LP12", "LP24", "HP", "BP", "OFF" };
        params.push_back(std::make_unique<AudioParameterChoice>(ParamID::filterType, "Filter Type", filterChoices, 0));
        auto cutoffRange = NormalisableRange<float>(20.f, 20000.f);
        cutoffRange.setSkewForCentre(1000.f);
        params.push_back(std::make_unique<AudioParameterFloat>(ParamID::filterCutoff, "Cutoff", cutoffRange, 8000.f));
        params.push_back(std::make_unique<AudioParameterFloat>(ParamID::filterRes, "Resonance",
            NormalisableRange<float>(0.f, 1.f, 0.01f), 0.f));
        params.push_back(std::make_unique<AudioParameterFloat>(ParamID::filterEnv, "Filter Env",
            NormalisableRange<float>(-1.f, 1.f, 0.01f), 0.f));

        // LFO
        params.push_back(std::make_unique<AudioParameterChoice>(ParamID::lfoWave, "LFO Wave", waveChoices, 0));
        auto lfoRateRange = NormalisableRange<float>(0.01f, 30.f);
        lfoRateRange.setSkewForCentre(2.f);
        params.push_back(std::make_unique<AudioParameterFloat>(ParamID::lfoRate, "LFO Rate", lfoRateRange, 2.f));
        params.push_back(std::make_unique<AudioParameterFloat>(ParamID::lfoToPitch, "LFO->Pitch",
            NormalisableRange<float>(-1.f, 1.f, 0.01f), 0.f));
        params.push_back(std::make_unique<AudioParameterFloat>(ParamID::lfoToCutoff, "LFO->Cutoff",
            NormalisableRange<float>(-1.f, 1.f, 0.01f), 0.f));
        params.push_back(std::make_unique<AudioParameterFloat>(ParamID::lfoToRes, "LFO->Res",
            NormalisableRange<float>(-1.f, 1.f, 0.01f), 0.f));
        params.push_back(std::make_unique<AudioParameterFloat>(ParamID::lfoToPW, "LFO->PW",
            NormalisableRange<float>(-1.f, 1.f, 0.01f), 0.f));

        // Distortion
        auto distChoices = StringArray { "Off", "Soft A", "Hard B" };
        params.push_back(std::make_unique<AudioParameterChoice>(ParamID::distMode, "Dist Mode", distChoices, 0));
        params.push_back(std::make_unique<AudioParameterFloat>(ParamID::distDrive, "Dist Drive",
            NormalisableRange<float>(0.f, 1.f, 0.01f), 0.f));

        return { params.begin(), params.end() };
    }
}

// Snapshot of all parameters — passed to voices on audio thread (no APVTS access there)
struct VoiceParams
{
    // OSC1
    int   osc1Wave    = 2;   // WaveShape index
    int   osc1Octave  = 0;
    int   osc1Semi    = 0;
    float osc1Fine    = 0.f;
    float osc1PW      = 0.5f;

    // OSC2
    int   osc2Wave    = 0;
    int   osc2Octave  = 0;
    int   osc2Semi    = 0;
    float osc2Fine    = 0.f;
    float osc2PW      = 0.5f;
    bool  osc2Sync    = false;

    // Mix
    float oscMix      = 0.5f;
    bool  ringMod     = false;

    // Envelope
    float envAttack   = 0.01f;
    float envDecay    = 0.1f;
    float envSustain  = 0.7f;
    float envSlope    = 0.5f;
    float envRelease  = 0.2f;

    // Filter
    int   filterType   = 0;   // FilterType index
    float filterCutoff = 8000.f;
    float filterRes    = 0.f;
    float filterEnv    = 0.f;

    // Distortion
    int   distMode     = 0;   // DistMode index
    float distDrive    = 0.f;
};

// LFO outputs — computed once per block, passed to each voice
struct VoiceModulation
{
    float lfoToPitch  = 0.f;   // semitones (lfo value * amount * scale)
    float lfoToCutoff = 0.f;   // Hz
    float lfoToRes    = 0.f;   // 0..1 delta
    float lfoToPW     = 0.f;   // 0..1 delta
};
