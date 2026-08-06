//
// Created by Joe Bristow on 29/07/2026.
//

#ifndef FMSU_TEXTURE_H
#define FMSU_TEXTURE_H

#include <juce_audio_basics/juce_audio_basics.h>

#include "EnvelopeFollower.h"
#include "NoiseGenerator.h"

class TextureLayer
{
public:
    void prepare(float sampleRate, size_t bufferSize);
    void process(juce::AudioBuffer<float>& buffer, size_t numSamples);
private:
    EnvelopeFollower _envelopeFollower {};
    NoiseGenerator _noiseGenerator {};
};


#endif //FMSU_TEXTURE_H
