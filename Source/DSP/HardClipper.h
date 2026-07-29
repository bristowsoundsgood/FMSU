//
// Created by Joe Bristow on 29/07/2026.
//

#ifndef FMSU_HARDCLIPPER_H
#define FMSU_HARDCLIPPER_H

#include <juce_audio_basics/juce_audio_basics.h>

class HardClipper
{
public:
    HardClipper();
    void update(float gain);
    void process(juce::AudioBuffer<float>& buffer, int numSamples);
private:
    float _gainMultiplier;

    float _applyGain(float x) const;
    float _applyNonLinearClip(float x) const;
};


#endif //FMSU_HARDCLIPPER_H
