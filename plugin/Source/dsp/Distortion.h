#pragma once

enum class DistMode { Off, SoftA, HardB };

class Distortion
{
public:
    // drive: 0..1
    float process(float x, float drive, DistMode mode) const;
};
