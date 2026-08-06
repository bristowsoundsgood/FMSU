//
// Created by Joe Bristow on 05/08/2026.
//

#include "NoiseGenerator.h"

float NoiseGenerator::getRandomSample() const
{
    const size_t randomIndex = static_cast<size_t>(static_cast<size_t>(random()) % (_buffer.getSize() + 1));
    return _buffer.getSample(randomIndex);
}

// Random number generator. Based on: https://github.com/hollance/synth-recipes/blob/main/recipes/white-noise.markdown
void NoiseGenerator::generateNoiseSamples(const size_t numSamples)
{
    _buffer.resize(numSamples);

    const long randomSeed = random();
    std::linear_congruential_engine<std::uint_fast32_t, 196314165, 907633515, 0> rng{ static_cast<std::uint_fast32_t>(randomSeed) };

    // For scaling generated numbers to the range [-1, 1]
    constexpr float scale = (2.0f / static_cast<float>(rng.max() + 1.0f));

    for (size_t i = 0; i < numSamples; ++i)
    {
        const std::uint_fast32_t randomInt = rng();
        const float randomFloat = (static_cast<float>(randomInt) * scale) - 1.0f;
        _buffer.setSample(i, randomFloat);
    }
}

size_t NoiseGenerator::getSize() const
{
    return _buffer.getSize();
}
