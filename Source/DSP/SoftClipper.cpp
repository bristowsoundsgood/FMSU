//
// Created by Joe on 21/06/2026.
//

#include "SoftClipper.h"
#include <cmath>

SoftClipper::SoftClipper() : _gainMultiplier(1.0f) {}

void SoftClipper::update(const float gain)
{
    _gainMultiplier = juce::Decibels::decibelsToGain(gain);
}

void SoftClipper::process(juce::AudioBuffer<float>& buffer, const int numSamples)
{
    float* leftChannel = buffer.getWritePointer(0);
    float* rightChannel = buffer.getWritePointer(1);

    for (int i = 0; i < numSamples; i++)
    {
        leftChannel[i] = _applyGain(leftChannel[i]);
        rightChannel[i] = _applyGain(rightChannel[i]);

        // Preserve stereo image: each channel gets the right amount of distortion based on sample amplitude
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


