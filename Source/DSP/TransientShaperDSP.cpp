//
// Created by Joe on 21/06/2026.
//

#include "TransientShaperDSP.h"
#include <juce_audio_basics/juce_audio_basics.h>

void TransientShaperDSP::update(const float attack, const float sustain)
{
    // === ENVELOPE PREP ===
    // if attack, then we want to apply transient boosting
    // n.b. attack can be negative to apply transient attenuation
    if (attack > 0.0f)
    {
        // the attack is not being used to set the attack of the envelope follower, it governs whether the fast envelope is looking for a transient
        _envelopeFast.setAttack(0.0f);
        _envelopeFast.setRelease(20.0f);

        _envelopeSlow.setAttack(20.0f);
        _envelopeSlow.setRelease(20.0f);
    }

    // if sustain then we want to apply body/sustain modification
    // n.b. sustain can be negative to apply body attenuation
    if (sustain > 0.0f)
    {
        _envelopeFast.setAttack(20.0f);
        _envelopeFast.setRelease(20.0f);

        _envelopeSlow.setAttack(20.0f);
        _envelopeSlow.setRelease(50.0f); // !! this might need to be longer?! or are we just finding the body without this method?
    }
}


void TransientShaperDSP::process(juce::AudioBuffer<float>& buffer)
{
    // === TRANSIENT SHAPING CODE === //
    float* leftChannel = buffer.getWritePointer(0);
    float* rightChannel = buffer.getWritePointer(1);
    const float numSamples = buffer.getNumSamples();

    for (int i = 0; i < numSamples; ++i)
    {
        // stereo-linked processing
        float controlSignal = (leftChannel[i] + rightChannel[i]) / 2.0f;

        // rectify
        controlSignal = fabsf(controlSignal);

        // get envelopes
        const float fastEnvelope = _envelopeFast.process(controlSignal);
        const float slowEnvelope = _envelopeSlow.process(controlSignal);

        float difference = fastEnvelope - slowEnvelope;

        constexpr float k = 2.0f;

        if (difference <= 0.0f)
        {
            difference = 0.0f;
        }

        const float gainCoefficient = 1.0f + (k * difference);
        leftChannel[i] = leftChannel[i] * gainCoefficient;
        rightChannel[i] = rightChannel[i] * gainCoefficient;
    }
}

void TransientShaperDSP::prepare(const float sampleRate)
{
    _envelopeFast.prepare(sampleRate);
    _envelopeSlow.prepare(sampleRate);
}





