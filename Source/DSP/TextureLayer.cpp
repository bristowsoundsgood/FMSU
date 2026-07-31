//
// Created by Joe Bristow on 29/07/2026.
//

#include "TextureLayer.h"

void TextureLayer::prepare(const float sampleRate)
{
    _envelopeFollower.prepare(sampleRate);

    _envelopeFollower.setAttack(0.0f);
    _envelopeFollower.setRelease(120.0f);
}

void TextureLayer::process(juce::AudioBuffer<float>& buffer, const size_t numSamples)
{
    const std::vector<float> noiseBuffer = _generateNoiseSamples(numSamples);

    float* leftChannel = buffer.getWritePointer(0);
    float* rightChannel = buffer.getWritePointer(1);

    for (size_t i = 0; i < numSamples; ++i)
    {
        const float dryL = leftChannel[i];
        const float dryR = rightChannel[i];

        const float controlSignal = fabsf(leftChannel[i] + rightChannel[i] / 2.0f); // Rectifying signal enables contouring of the waveform

        // Envelope modulates the volume of the white noise (i.e., the noise follows the contour of the waveform)

        const float _envelope = _envelopeFollower.process(controlSignal);
        const float noiseSample = noiseBuffer[i] * _envelope;

        // Blend noise with original signal

        constexpr float wetMix = 0.015f;

        leftChannel[i] = dryL * (1.0f - wetMix) + noiseSample * (wetMix);
        rightChannel[i] = dryR * (1.0f - wetMix) + noiseSample * (wetMix);
    }
}

std::vector<float> TextureLayer::_generateNoiseSamples(const size_t numSamples) const
{
    // Random number generator. Based on: https://github.com/hollance/synth-recipes/blob/main/recipes/white-noise.markdown

    const long randomSeed = random();
    std::linear_congruential_engine<std::uint_fast32_t, 196314165, 907633515, 0> rng{ static_cast<std::uint_fast32_t>(randomSeed) };

    // For scaling generated numbers to the range [-1, 1]
    constexpr float scale = (2.0f / static_cast<float>(rng.max() + 1.0f));

    std::vector<float> buffer(numSamples);

    for (size_t i = 0; i < numSamples; ++i)
    {
        const std::uint_fast32_t randomInt = rng();
        const float randomFloat = (static_cast<float>(randomInt) * scale) - 1.0f;
        buffer[i] = randomFloat;
    }

    return buffer;
}
