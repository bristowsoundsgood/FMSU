//
// Created by Joe Bristow on 06/08/2026.
//

#ifndef FMSU_STEREOWIDENER_H
#define FMSU_STEREOWIDENER_H

#include <juce_audio_basics/juce_audio_basics.h>

class StereoWidener
{
public:
    void process(juce::AudioBuffer<float>& buffer, size_t numSamples) const;
    void update(float coefficient);
private:
    float _coefficient {};
};


#endif //FMSU_STEREOWIDENER_H
