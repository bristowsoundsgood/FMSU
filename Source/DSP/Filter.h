//
// Created by Joe Bristow on 31/07/2026.
//

#ifndef FMSU_FIRFILTER_H
#define FMSU_FIRFILTER_H

#include <juce_audio_basics/juce_audio_basics.h>

class Filter
{
public:
    void setHighPass(bool isHighPass);
    void prepare(float sampleRate);
    void update(float cutoffFrequencyHz);
    void process(juce::AudioBuffer<float>& buffer, size_t numSamples);
    float process(float inputSample, unsigned int channel);
private:
    bool _isHighPass { true };

    float _sampleRate {};
    float _coefficient {};

    float _delayL {};
    float _delayR {};

    [[nodiscard]] float _convertFrequencyToNormalisedUnits(float frequencyHz) const;
};


#endif //FMSU_FIRFILTER_H
