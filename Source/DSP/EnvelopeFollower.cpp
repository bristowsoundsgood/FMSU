//
// Created by Joe on 29/05/2026.
//

#include "EnvelopeFollower.h"

#include <cmath>

EnvelopeFollower::EnvelopeFollower()
{
}

void EnvelopeFollower::prepare(const float sampleRate)
{
    _sampleRate = sampleRate;
}


// do we want to update the reference, or do we want a control signal?
float EnvelopeFollower::process(float sample)
{
    sample = fabsf(sample);

    if (sample > _envelope)
    {
        _envelope = _attack * (_envelope - sample) + sample;
    }

    else
    {
        _envelope = _release * (_envelope - sample) + sample;
    }

    return _envelope;
}

void EnvelopeFollower::setAttack(const float milliseconds)
{
    // convert ms to a scalar value
    _attack = _convertToScalarMultiplier(milliseconds);
}

void EnvelopeFollower::setRelease(const float milliseconds)
{
    _release = _convertToScalarMultiplier(milliseconds);
}

float EnvelopeFollower::_convertToScalarMultiplier(const float milliseconds) const
{
    return pow(0.01f, 1.0f / (milliseconds * _sampleRate * 0.001f));
}

