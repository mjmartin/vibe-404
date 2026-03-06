#include "Distortion.h"
#include <cmath>
#include <JuceHeader.h>

float Distortion::process(float x, float drive, DistMode mode) const
{
    switch (mode)
    {
        case DistMode::Off:
            return x;

        case DistMode::SoftA:
        {
            // Normalised tanh soft-clip
            float gain = 1.f + drive * 9.f;
            float denom = std::tanh(gain);
            if (denom < 1e-6f) return x;
            return std::tanh(x * gain) / denom;
        }

        case DistMode::HardB:
        {
            // Hard clip at threshold, then normalise
            float threshold = 1.f - drive * 0.9f;
            threshold = juce::jmax(0.1f, threshold);
            float clipped = juce::jlimit(-threshold, threshold, x);
            return clipped / threshold;
        }
    }

    return x;
}
