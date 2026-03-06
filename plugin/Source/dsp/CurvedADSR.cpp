#include "CurvedADSR.h"
#include <cmath>

void CurvedADSR::prepare(double sr)
{
    sampleRate = sr;
    stage = Stage::Idle;
    output = 0.0;
}

// EarLevel formula: coef = exp(-log((1+ratio)/ratio) / (time * sr))
double CurvedADSR::calcCoef(double timeSec, double sr, double targetRatio)
{
    if (timeSec <= 0.0)
        return 0.0;
    return std::exp(-std::log((1.0 + targetRatio) / targetRatio) / (timeSec * sr));
}

void CurvedADSR::setParameters(float attack, float decay, float sustain, float release, float slope)
{
    // slope 0..1 → targetRatio 0.0001..1.0 (exponential..near-linear)
    double ratio = juce::jmap<double>(static_cast<double>(slope), 0.0, 1.0, 0.0001, 1.0);

    attackCoef  = calcCoef(attack, sampleRate, ratio);
    attackBase  = (1.0 + ratio) * (1.0 - attackCoef);

    decayCoef   = calcCoef(decay, sampleRate, ratio);
    decayBase   = (static_cast<double>(sustain) - ratio) * (1.0 - decayCoef);

    sustainLevel = static_cast<double>(sustain);

    releaseCoef  = calcCoef(release, sampleRate, ratio);
    releaseBase  = -ratio * (1.0 - releaseCoef);
}

void CurvedADSR::noteOn()
{
    stage = Stage::Attack;
}

void CurvedADSR::noteOff()
{
    if (stage != Stage::Idle)
        stage = Stage::Release;
}

bool CurvedADSR::isActive() const
{
    return stage != Stage::Idle;
}

float CurvedADSR::processSample()
{
    switch (stage)
    {
        case Stage::Attack:
            output = attackBase + output * attackCoef;
            if (output >= 1.0)
            {
                output = 1.0;
                stage = Stage::Decay;
            }
            break;

        case Stage::Decay:
            output = decayBase + output * decayCoef;
            if (output <= sustainLevel)
            {
                output = sustainLevel;
                stage = Stage::Sustain;
            }
            break;

        case Stage::Sustain:
            output = sustainLevel;
            break;

        case Stage::Release:
            output = releaseBase + output * releaseCoef;
            if (output <= 0.0001)
            {
                output = 0.0;
                stage = Stage::Idle;
            }
            break;

        case Stage::Idle:
        default:
            output = 0.0;
            break;
    }

    return static_cast<float>(output);
}
