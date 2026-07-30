//
// Created by Joe Bristow on 29/07/2026.
//

#include "HardClipper.h"

HardClipper::HardClipper()
{
    _gainMultiplier = 1.0f;
}

void HardClipper::update(const float gain)
{
    _gainMultiplier = juce::Decibels::decibelsToGain(gain);
}

void HardClipper::process(juce::AudioBuffer<float>& buffer, const size_t numSamples)
{
    float* leftChannel = buffer.getWritePointer(0);
    float* rightChannel = buffer.getWritePointer(1);

    for (size_t i = 0; i < numSamples; ++i)
    {
        leftChannel[i] = _applyGain(leftChannel[i]);
        rightChannel[i] = _applyGain(rightChannel[i]);

        leftChannel[i] = _applyNonLinearClip(leftChannel[i]);
        rightChannel[i] = _applyNonLinearClip((rightChannel[i]));
    }
}

float HardClipper::_applyNonLinearClip(const float x) const
{
    if (x <= -1.0f) return -1.0f;
    if (x > -1.0f && x < 1.0f) return x;
    return 1.0f;
}

float HardClipper::_applyGain(float x) const
{
    return x * _gainMultiplier;
}
