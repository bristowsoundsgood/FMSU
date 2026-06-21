//
// Created by Joe on 21/06/2026.
//

#ifndef FMSU_TRANSIENTSHAPERDSP_H
#define FMSU_TRANSIENTSHAPERDSP_H

#include "EnvelopeFollower.h"
#include <juce_audio_processors/juce_audio_processors.h>

class TransientShaperDSP
{
public:
    void prepare(float sampleRate);
    void update(float attack, float sustain);
    void process(juce::AudioBuffer<float>& buffer);
private:
    EnvelopeFollower _envelopeSlow {};
    EnvelopeFollower _envelopeFast {};
};


#endif //FMSU_TRANSIENTSHAPERDSP_H