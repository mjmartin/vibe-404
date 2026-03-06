#pragma once
#include <JuceHeader.h>

enum class WaveShape { Sine, Tri, Saw, RevSaw, Square, Noise };

class PolyBlepOscillator
{
public:
    void prepare(double sampleRate);
    void setFrequency(double hz);
    void setPulseWidth(float pw);     // 0.01..0.99
    void setWaveShape(WaveShape ws);

    // Reset phase to 0 (used for hard sync)
    void reset();

    // Returns true if phase wrapped this sample (for hard-sync detection)
    bool didReset() const { return phaseReset; }

    float processSample();

private:
    static float polyBlep(float t, float dt);

    WaveShape shape      = WaveShape::Saw;
    double    sampleRate = 44100.0;
    double    phase      = 0.0;
    double    phaseInc   = 0.0;
    float     pulseWidth = 0.5f;
    float     triAccum   = 0.0f;   // leaky integrator for triangle
    bool      phaseReset = false;
};
