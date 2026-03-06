#include "PolyBlepOscillator.h"
#include <cmath>

void PolyBlepOscillator::prepare(double sr)
{
    sampleRate = sr;
    phase = 0.0;
    triAccum = 0.f;
}

void PolyBlepOscillator::setFrequency(double hz)
{
    phaseInc = hz / sampleRate;
}

void PolyBlepOscillator::setPulseWidth(float pw)
{
    pulseWidth = juce::jlimit(0.01f, 0.99f, pw);
}

void PolyBlepOscillator::setWaveShape(WaveShape ws)
{
    shape = ws;
}

void PolyBlepOscillator::reset()
{
    phase = 0.0;
    triAccum = 0.f;
}

// polyBLEP residual, t = normalised phase (0..1), dt = phaseInc
float PolyBlepOscillator::polyBlep(float t, float dt)
{
    if (t < dt)
    {
        t /= dt;
        return t + t - t * t - 1.f;
    }
    else if (t > 1.f - dt)
    {
        t = (t - 1.f) / dt;
        return t * t + t + t + 1.f;
    }
    return 0.f;
}

float PolyBlepOscillator::processSample()
{
    phaseReset = false;
    auto t = static_cast<float>(phase);
    auto dt = static_cast<float>(phaseInc);

    float out = 0.f;

    switch (shape)
    {
        case WaveShape::Sine:
            out = std::sin(juce::MathConstants<float>::twoPi * t);
            break;

        case WaveShape::Saw:
            out = 2.f * t - 1.f;
            out -= polyBlep(t, dt);
            break;

        case WaveShape::RevSaw:
            out = 1.f - 2.f * t;
            out += polyBlep(t, dt);
            break;

        case WaveShape::Square:
        {
            out = (t < pulseWidth) ? 1.f : -1.f;
            out += polyBlep(t, dt);
            out -= polyBlep(std::fmod(t + 1.f - pulseWidth, 1.f), dt);
            break;
        }

        case WaveShape::Tri:
        {
            // Generate corrected square, then integrate
            float sq = (t < pulseWidth) ? 1.f : -1.f;
            sq += polyBlep(t, dt);
            sq -= polyBlep(std::fmod(t + 1.f - pulseWidth, 1.f), dt);
            // Leaky integrator (4 * dt * sq) — DC-compensated
            triAccum = triAccum * 0.9999f + 4.f * dt * sq;
            out = triAccum;
            break;
        }

        case WaveShape::Noise:
            out = juce::Random::getSystemRandom().nextFloat() * 2.f - 1.f;
            break;
    }

    phase += phaseInc;
    if (phase >= 1.0)
    {
        phase -= 1.0;
        phaseReset = true;
    }

    return out;
}
