//
// Created by Joe Bristow on 29/07/2026.
//

#ifndef FMSU_TEXTURE_H
#define FMSU_TEXTURE_H

#include <juce_audio_basics/juce_audio_basics.h>

#include <random>
#include "EnvelopeFollower.h"

class TextureLayer
{
public:
    void prepare(float sampleRate);
    void process(juce::AudioBuffer<float>& buffer, size_t numSamples);
    [[nodiscard]] std::vector<float> _generateNoiseSamples(size_t numSamples) const;
private:
    EnvelopeFollower _envelopeFollower {};
};


#endif //FMSU_TEXTURE_H
