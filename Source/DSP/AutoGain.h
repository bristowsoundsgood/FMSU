//
// Created by Joe Bristow on 20/07/2026.
//

#ifndef FMSU_AUTOGAIN_H
#define FMSU_AUTOGAIN_H

#include <juce_audio_basics/juce_audio_basics.h>

class AutoGain
{
public:
    void readInput(const juce::AudioBuffer<float>& buffer, int numSamples);
    void readOutput(const juce::AudioBuffer<float>& buffer, int numSamples);
    void applyGain(juce::AudioBuffer<float>& buffer, int numSamples);

private:
    float _inRMS;
    float _outRMS;
};


#endif //FMSU_AUTOGAIN_H
