//
// Created by Joe on 21/06/2026.
//

#include "TransientShaper.h"
#include <juce_audio_basics/juce_audio_basics.h>

/*
 * - Detect body of a signal (difference <= 0.0f)
 * - Use _sustain value to modulate the gain parameter applied to the body
 */

void TransientShaper::prepare(const float sampleRate)
{
    _signalEnvelope.prepare(sampleRate);
    _signalEnvelope.setAttack(SIGNAL_ENVELOPE_ATTACK);
    _signalEnvelope.setRelease(BODY_ENVELOPE_RELEASE);

    _bodyEnvelope.prepare(sampleRate);
    _bodyEnvelope.setAttack(BODY_ENVELOPE_ATTACK);
    _bodyEnvelope.setRelease(BODY_ENVELOPE_RELEASE);

    _sustainEnvelope.prepare(sampleRate);
    _sustainEnvelope.setAttack(SIGNAL_ENVELOPE_ATTACK);
    _sustainEnvelope.setRelease(2000.0f);
}

void TransientShaper::update(const float attack, const float sustain)
{
    _attack = attack;
    _sustain = sustain;
}

void TransientShaper::process(juce::AudioBuffer<float>& buffer, const int numSamples)
{
    float* leftChannel = buffer.getWritePointer(0);
    float* rightChannel = buffer.getWritePointer(1);

    // // AutoGain: Measure RMS of input
    // const float inputRMS = buffer.getRMSLevel(0, 0, numSamples);

    // Transient processing
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

        const float transientCoefficient = 1.0f + (_attack * attackDifference);
        const float sustainCoefficient = 1.0f + (_sustain * sustainDifference);

        // Transient detected
        if (attackDifference > 0.0f)
        {
            leftChannel[i] = leftChannel[i] * transientCoefficient;
            rightChannel[i] = rightChannel[i] * transientCoefficient;
        }

        // Body detected
        if (sustainDifference > 0.0f)
        {
            leftChannel[i] = leftChannel[i] * sustainCoefficient;
            rightChannel[i] = rightChannel[i] * sustainCoefficient;
        }
    }

    //     // AutoGain: Measure RMS of output
    //     const float outputRMS = buffer.getRMSLevel(0, 0, numSamples);
    //
    //     // ...scale output to be RMS-matched (i.e., roughly volume-matched) with the input.
    //     // This prevents loud transientShaper outputs being interpreted as 'better'
    //     const float autoGainCoefficient = inputRMS / outputRMS;
    //     for (int i = 0; i < numSamples; i++)
    //     {
    //         const float beforeL = leftChannel[i];
    //         const float beforeR = rightChannel[i];
    //
    //         leftChannel[i] *= autoGainCoefficient;
    //         rightChannel[i] *= autoGainCoefficient;
    //
    //         if (i == numSamples - 1)
    //         {
    // std::cout << "beforeL: " << beforeL << " | " << "afterL: " << leftChannel[i] << '\n';
    // std::cout << "beforeR: " << beforeR << " | " << "afterR: " << rightChannel[i] << '\n';
    // std::cout << "autoGainCoefficient: " << autoGainCoefficient << '\n';
    // std::cout << "-------------------------------------------" << '\n';
    //         }
// }
}




