//
// Created by Joe Bristow on 29/07/2026.
//

#include "TextureLayer.h"

void TextureLayer::prepare(const float sampleRate)
{
    _envelopeFollower.prepare(sampleRate);

    // TODO: Set as static variables
    _envelopeFollower.setAttack(0.0f);
    _envelopeFollower.setRelease(120.0f);
}

void TextureLayer::process(juce::AudioBuffer<float>& buffer, const size_t numSamples)
{
    const std::vector<float> noiseSamples = _generateNoiseSamples(numSamples);

    for (size_t i = 0; i < numSamples; ++i)
    {

    }

    // contour signal
    // apply noise to envelope
    // blend via. dry/wet
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
