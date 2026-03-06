#pragma once
#include <JuceHeader.h>

// EarLevel-style exponential ADSR with configurable curve slope.
// slope param maps to targetRatio: 0.0001 = very exponential, 1.0 = near-linear.
class CurvedADSR
{
public:
    void prepare(double sampleRate);

    // All times in seconds; slope 0..1
    void setParameters(float attack, float decay, float sustain, float release, float slope);

    void noteOn();
    void noteOff();

    bool isActive() const;

    float processSample();

private:
    enum class Stage { Idle, Attack, Decay, Sustain, Release };

    static double calcCoef(double timeSec, double sampleRate, double targetRatio);

    Stage  stage      = Stage::Idle;
    double sampleRate = 44100.0;
    double output     = 0.0;

    // Coefficients and targets (recomputed on setParameters)
    double attackCoef   = 0.0, attackBase   = 0.0;
    double decayCoef    = 0.0, decayBase    = 0.0;
    double releaseCoef  = 0.0, releaseBase  = 0.0;
    double sustainLevel = 0.7;
};
