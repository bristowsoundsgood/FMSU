//
// Created by Joe Bristow on 31/07/2026.
//

#include "Filter.h"

#include <juce_graphics/fonts/harfbuzz/hb-subset.h>

#include "../Consts.h"

void Filter::prepare(const float sampleRate)
{
    _sampleRate = sampleRate;
}


void Filter::update(const float cutoffFrequencyHz)
{
    const float normalisedUnits = _convertFrequencyToNormalisedUnits(cutoffFrequencyHz);
    const float tan = static_cast<float>(std::tan(Consts::PI * normalisedUnits));
    _coefficient = (tan - 1.0f) / (tan + 1.0f);
}

void Filter::process(juce::AudioBuffer<float>& buffer, const size_t numSamples)
{
    float* leftChannel = buffer.getWritePointer(0);
    float* rightChannel = buffer.getWritePointer(1);

    const float sign = _isHighPass ? -1.0f : 1.0f;

    for (size_t i = 0; i < numSamples; ++i)
    {
        const float dryL = leftChannel[i];
        const float filteredL = _coefficient * dryL + _delayL;
        const float wetL = 0.5f * (dryL + sign * filteredL);
        _delayL = dryL - (filteredL * _coefficient);

        const float dryR = leftChannel[i];
        const float filteredR = _coefficient * dryR + _delayR;
        const float wetR = 0.5f * (dryR + sign * filteredR);
        _delayR = dryR - (filteredR * _coefficient);

        leftChannel[i] = wetL;
        rightChannel[i] = wetR;
    }
}

float Filter::process(const float inputSample, const unsigned int channel)
{
    const float sign = _isHighPass ? -1.0f : 1.0f;

    if (channel == 0)
    {
        const float filteredL = _coefficient * inputSample + _delayL;
        const float wetL = 0.5f * (inputSample + sign * filteredL);
        _delayL = inputSample - (filteredL * _coefficient);

        return wetL;
    }

    const float filteredR = _coefficient * inputSample + _delayR;
    const float wetR = 0.5f * (inputSample + sign * filteredR);
    _delayR = inputSample - (filteredR * _coefficient);

    return wetR;
}

float Filter::_convertFrequencyToNormalisedUnits(const float frequencyHz) const
{
    // The 'Hz' units are cancelled in this equation, returning a unit with no physical units (normalised)
    return frequencyHz / _sampleRate;
}

void Filter::setHighPass(const bool isHighPass)
{
    _isHighPass = isHighPass;
}
