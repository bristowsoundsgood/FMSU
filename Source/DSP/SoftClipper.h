//
// Created by Joe on 21/06/2026.
//

#ifndef FMSU_SOFTCLIPPERDSP_H
#define FMSU_SOFTCLIPPERDSP_H

#include <juce_audio_processors/juce_audio_processors.h>

class SoftClipper
{
public:
    SoftClipper();
    void update(float gain);
    void process(juce::AudioBuffer<float>& buffer, int numSamples);
private:
    float _applyGain(float x) const;
    float _applyCubicNonlinearity(float x);
    float _convertDecibelsToLinearUnits(float gain);

    float _gainMultiplier;
};


#endif //FMSU_SOFTCLIPPERDSP_H