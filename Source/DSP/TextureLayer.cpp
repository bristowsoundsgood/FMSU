//
// Created by Joe Bristow on 29/07/2026.
//

#include "TextureLayer.h"

void TextureLayer::prepare(const float sampleRate, const size_t bufferSize)
{
    _envelopeFollower.prepare(sampleRate);
    _envelopeFollower.setAttack(0.0f);
    _envelopeFollower.setRelease(120.0f);

    _highPassFilter.prepare(sampleRate);
    _noiseGenerator.generateNoiseSamples(bufferSize);
}

void TextureLayer::process(juce::AudioBuffer<float>& buffer, const size_t numSamples)
{
    float* leftChannel = buffer.getWritePointer(0);
    float* rightChannel = buffer.getWritePointer(1);

    for (size_t i = 0; i < numSamples; ++i)
    {
        const float dryL = leftChannel[i];
        const float dryR = rightChannel[i];

        const float controlSignal = fabsf(leftChannel[i] + rightChannel[i] / 2.0f); // Rectifying signal enables contouring of the waveform

        // Envelope modulates the volume of the white noise (i.e., the noise follows the contour of the waveform)
        const float _envelope = _envelopeFollower.process(controlSignal);

        const float noiseSample = _noiseGenerator.getRandomSample() * _envelope;

        const float wetL = dryL * noiseSample;
        const float wetR = dryR * noiseSample;

        // Blend noise with original signal
        constexpr float wetMix = 0.01f;
        leftChannel[i] = dryL * (1.0f - wetMix) + wetL * (wetMix);
        rightChannel[i] = dryR * (1.0f - wetMix) + wetR * (wetMix);
    }
}
