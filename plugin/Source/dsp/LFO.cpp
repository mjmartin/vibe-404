#include "LFO.h"

void LFO::prepare(double sampleRate)
{
    osc.prepare(sampleRate);
}

void LFO::setRate(float hz)
{
    osc.setFrequency(juce::jlimit(0.01f, 30.f, hz));
}

void LFO::setWaveShape(WaveShape ws)
{
    osc.setWaveShape(ws);
}

float LFO::processSample()
{
    return osc.processSample();
}
