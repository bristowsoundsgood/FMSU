//
// Created by Joe on 21/06/2026.
//

#include "SoftClipper.h"
#include <cmath>

SoftClipper::SoftClipper() : _gainMultiplier(1.0f) {}

void SoftClipper::update(const float gain)
{
    _gainMultiplier = _convertDecibelsToLinearUnits(gain);
}

void SoftClipper::process(juce::AudioBuffer<float>& buffer)
{
    const int numSamples = buffer.getNumSamples();

    float* leftChannel = buffer.getWritePointer(0);
    float* rightChannel = buffer.getWritePointer(1);

    for (int i = 0; i < numSamples; i++)
    {
        leftChannel[i] = _applyGain(leftChannel[i]);
        rightChannel[i] = _applyGain(rightChannel[i]);

        leftChannel[i] = _applyCubicNonlinearity(leftChannel[i]);
        rightChannel[i] = _applyCubicNonlinearity(rightChannel[i]);
    }
}

float SoftClipper::_applyCubicNonlinearity(const float x)
{
    if (x <= -1.0f) return -2.0f / 3.0f;
    if (x < 1.0f) return x - (x * x * x) / 3.0f;
    return 2.0f / 3.0f;
}

float SoftClipper::_applyGain(const float x) const
{
    return x * _gainMultiplier;
}

float SoftClipper::_convertDecibelsToLinearUnits(const float gain)
{
    return std::powf(10, gain / 20);
}



