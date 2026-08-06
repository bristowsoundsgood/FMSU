//
// Created by Joe Bristow on 06/08/2026.
//

#include "StereoWidener.h"

void StereoWidener::update(const float coefficient)
{
    _coefficient = coefficient / 2.0f; // Halved because 2 channels are being processed
}

void StereoWidener::process(juce::AudioBuffer<float>& buffer, const size_t numSamples) const
{
    float* leftChannel = buffer.getWritePointer(0);
    float* rightChannel = buffer.getWritePointer(1);

    for (size_t i = 0; i < numSamples; ++i)
    {
        const float dryL = leftChannel[i];
        const float dryR = rightChannel[i];

        // Mid-side processing (width is added by multiplying the side information by the coefficient)

        const float mid = (dryL + dryR) / 2.0f;
        const float side = (dryR - dryL) * _coefficient;

        const float wetL = mid - side;
        const float wetR = mid + side;

        leftChannel[i] = wetL;
        rightChannel[i] = wetR;
    }
}

