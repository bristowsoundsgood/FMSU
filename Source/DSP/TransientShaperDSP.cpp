//
// Created by Joe on 21/06/2026.
//

#include "TransientShaperDSP.h"
#include <juce_audio_basics/juce_audio_basics.h>

void TransientShaperDSP::prepare(const float sampleRate)
{
    // Built-in envelope followers.
    // The difference between them (fast - slow) is used to detect a transient (positive difference) or body (0 or negative difference).
    _envelopeFast.prepare(sampleRate);
    _envelopeSlow.prepare(sampleRate);

    _envelopeFast.setAttack(0.0f);
    _envelopeFast.setRelease(20.0f);

    _envelopeSlow.setAttack(20.0f);
    _envelopeSlow.setRelease(20.0f);
}

void TransientShaperDSP::update(const float attack, const float sustain)
{
    // Attack/sustain values modulate the gain modification of transient/body, respectively.
    _attack = attack;
    _sustain = sustain;
}

void TransientShaperDSP::process(juce::AudioBuffer<float>& buffer)
{
    // === TRANSIENT SHAPING CODE === //
    float* leftChannel = buffer.getWritePointer(0);
    float* rightChannel = buffer.getWritePointer(1);
    const int numSamples = buffer.getNumSamples();

    for (int i = 0; i < numSamples; ++i)
    {
        // stereo-linked processing
        float controlSignal = (leftChannel[i] + rightChannel[i]) / 2.0f;

        // rectify
        controlSignal = fabsf(controlSignal);

        // difference > 0 : transient detected. difference <= 0 : body detected.
        const float fastEnvelopeValue = _envelopeFast.process(controlSignal);
        const float slowEnvelopeValue = _envelopeSlow.process(controlSignal);
        float difference = fastEnvelopeValue - slowEnvelopeValue;

        if (difference <= 0.0f)
        {
            difference = 0.0f;
            // do something here for processing the sustain
        }

        // If the attack is 0, then the signal remains unaffected.
        const float gainCoefficient = 1.0f + (_attack * difference);
        leftChannel[i] = leftChannel[i] * gainCoefficient;
        rightChannel[i] = rightChannel[i] * gainCoefficient;
    }
}





