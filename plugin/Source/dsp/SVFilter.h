#pragma once
#include <JuceHeader.h>

enum class FilterType { LP12, LP24, HP, BP, Off };

class SVFilter
{
public:
    void prepare(const juce::dsp::ProcessSpec& spec);

    void setType(FilterType t);
    void setCutoff(float hz);
    void setResonance(float q);   // 0..1, mapped to Q factor internally

    float processSample(float x);

private:
    using TPTFilter = juce::dsp::StateVariableTPTFilter<float>;

    void updateCoefficients();

    FilterType type       = FilterType::LP12;
    float      cutoffHz   = 8000.f;
    float      resonance  = 0.f;
    double     sampleRate = 44100.0;

    TPTFilter filterA;   // primary (all modes)
    TPTFilter filterB;   // secondary (LP24 cascade only)
};
