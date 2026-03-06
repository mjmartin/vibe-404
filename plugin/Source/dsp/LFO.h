#pragma once
#include "PolyBlepOscillator.h"

class LFO
{
public:
    void prepare(double sampleRate);
    void setRate(float hz);
    void setWaveShape(WaveShape ws);

    // Returns -1..+1
    float processSample();

private:
    PolyBlepOscillator osc;
};
