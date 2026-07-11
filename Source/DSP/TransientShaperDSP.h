//
// Created by Joe on 21/06/2026.
//

#ifndef FMSU_TRANSIENTSHAPERDSP_H
#define FMSU_TRANSIENTSHAPERDSP_H

#include "EnvelopeFollower.h"
#include <juce_audio_processors/juce_audio_processors.h>

// Architecture from: https://spl.audio/en/spl-produkt/transient-designer-4-mk2/
class TransientShaperDSP
{
public:
    void prepare(float sampleRate);
    void update(float attack, float sustain);
    void process(juce::AudioBuffer<float>& buffer);
private:
    float _attack {};
    float _sustain {};

    EnvelopeFollower _signalEnvelope {};    // Follows the signal's true shape. Fast attack captures transient.
    EnvelopeFollower _bodyEnvelope {};      // Follows the body of the signal. Slow attack misses transient.
    EnvelopeFollower _sustainEnvelope{};    // Long-sustain envelope. Slow release. Captures transient and an overly-pronounced body.

    // differenceAttack = SignalEnvelope - BodyEnvelope
    // differenceBody =  SustainEnvelope - SignalEnvelope
    // These difference values modulate the control signal, used when calculating a gain multiplier for the audio signal.
};


#endif //FMSU_TRANSIENTSHAPERDSP_H