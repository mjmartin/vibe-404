#include "SVFilter.h"

void SVFilter::prepare(const juce::dsp::ProcessSpec& spec)
{
    sampleRate = spec.sampleRate;
    filterA.prepare(spec);
    filterB.prepare(spec);
    filterA.reset();
    filterB.reset();
}

void SVFilter::setType(FilterType t)
{
    type = t;
    updateCoefficients();
}

void SVFilter::setCutoff(float hz)
{
    cutoffHz = juce::jlimit(20.f, 20000.f, hz);
    updateCoefficients();
}

void SVFilter::setResonance(float q)
{
    resonance = juce::jlimit(0.f, 1.f, q);
    updateCoefficients();
}

void SVFilter::updateCoefficients()
{
    // Map resonance 0..1 → Q 0.5..10
    float qFactor = juce::jmap(resonance, 0.f, 1.f, 0.5f, 10.f);

    switch (type)
    {
        case FilterType::LP12:
        case FilterType::LP24:
            filterA.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
            filterB.setType(juce::dsp::StateVariableTPTFilterType::lowpass);
            break;
        case FilterType::HP:
            filterA.setType(juce::dsp::StateVariableTPTFilterType::highpass);
            break;
        case FilterType::BP:
            filterA.setType(juce::dsp::StateVariableTPTFilterType::bandpass);
            break;
        case FilterType::Off:
            return;
    }

    filterA.setCutoffFrequency(cutoffHz);
    filterA.setResonance(qFactor);

    if (type == FilterType::LP24)
    {
        filterB.setCutoffFrequency(cutoffHz);
        filterB.setResonance(qFactor);
    }
}

float SVFilter::processSample(float x)
{
    if (type == FilterType::Off)
        return x;

    float out = filterA.processSample(0, x);

    if (type == FilterType::LP24)
        out = filterB.processSample(0, out);

    return out;
}
