//
// Created by Joe on 21/06/2026.
//

#include "TransientShaperDSP.h"
#include <juce_audio_basics/juce_audio_basics.h>

/*
 * - Detect body of a signal (difference <= 0.0f)
 * - Use _sustain value to modulate the gain parameter applied to the body
 */

void TransientShaperDSP::prepare(const float sampleRate)
{
    _signalEnvelope.prepare(sampleRate);
    _signalEnvelope.setAttack(0.0f);
    _signalEnvelope.setRelease(20.0f);

    _bodyEnvelope.prepare(sampleRate);
    _bodyEnvelope.setAttack(20.0f);
    _bodyEnvelope.setRelease(20.0f);

    _sustainEnvelope.prepare(sampleRate);
    _sustainEnvelope.setAttack(0.0f);
    _sustainEnvelope.setRelease(500.0f);
}

void TransientShaperDSP::update(const float attack, const float sustain)
{
    // Attack/sustain values modulate the gain modification of transient/body, respectively.
    _attack = attack;
    _sustain = sustain;
}

void TransientShaperDSP::process(juce::AudioBuffer<float>& buffer)
{
    float* leftChannel = buffer.getWritePointer(0);
    float* rightChannel = buffer.getWritePointer(1);
    const int numSamples = buffer.getNumSamples();

    for (int i = 0; i < numSamples; ++i)
    {
        // Stereo-linked processing
        float controlSignal = (leftChannel[i] + rightChannel[i]) / 2.0f;

        // Absolute values enable transient extraction (draws contour of waveform)
        controlSignal = fabsf(controlSignal);

        const float signalEnvelopeValue = _signalEnvelope.process(controlSignal);
        const float bodyEnvelopeValue = _bodyEnvelope.process(controlSignal);
        const float sustainEnvelopeValue = _sustainEnvelope.process(controlSignal);

        const float attackDifference = signalEnvelopeValue - bodyEnvelopeValue;
        const float sustainDifference = sustainEnvelopeValue - signalEnvelopeValue;

        // Transient detected
        if (attackDifference > 0.0f)
        {
            // If the attack is 0, the signal remains unaffected.
            const float transientCoefficient = 1.0f + (_attack * attackDifference);
            leftChannel[i] = leftChannel[i] * transientCoefficient;
            rightChannel[i] = rightChannel[i] * transientCoefficient;
        }

        // Body detected
        if (sustainDifference > 0.0f)
        {
            const float sustainCoefficient = 1.0f + (_sustain * sustainDifference);
            leftChannel[i] = leftChannel[i] * sustainCoefficient;
            rightChannel[i] = rightChannel[i] * sustainCoefficient;
        }
    }
}





