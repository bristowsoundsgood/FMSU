//
// Created by Joe on 21/06/2026.
//

#include "SoftClipperDSP.h"

SoftClipperDSP::SoftClipperDSP() : _gainMultiplier(1.0f) {};

void SoftClipperDSP::update(const float gain)
{
    _gainMultiplier = _convertDecibelsToLinearUnits(gain);
}

void SoftClipperDSP::process(juce::AudioBuffer<float>& buffer)
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

float SoftClipperDSP::_applyCubicNonlinearity(const float x)
{
    if (x <= -1.0f) return -2.0f / 3.0f;
    else if (x < 1.0f) return x - (x * x * x) / 3.0f;
    else return 2.0f / 3.0f;
}

float SoftClipperDSP::_applyGain(const float x) const
{
    return x * _gainMultiplier;
}

float SoftClipperDSP::_convertDecibelsToLinearUnits(const float gain)
{
    return pow<float>(10, gain / 20);
}



