//
// Created by Joe on 29/05/2026.
//

#include "EnvelopeFollower.h"
#include <cmath>

void EnvelopeFollower::prepare(const float sampleRate)
{
    _sampleRate = sampleRate;
}

float EnvelopeFollower::process(float sample)
{

    // Rectify
    sample = fabsf(sample);

    if (sample < _envelope)
    {
        _envelope += _attack * (sample - _envelope);
    }

    else
    {
        _envelope += _sustain * (sample - _envelope);
    }

    return _envelope;
}

void EnvelopeFollower::setAttack(const float milliseconds)
{
    _attack = convertToScale(milliseconds);
}

void EnvelopeFollower::setSustain(const float milliseconds)
{
    _sustain = convertToScale(milliseconds);
}

float EnvelopeFollower::convertToScale(const float milliseconds)
{
    if (milliseconds <= 0.f || _sampleRate <= 0.f)
    {
        return 1.0f;
    }

    return 1.0f - exp(-1.f / (milliseconds * 0.001f * _sampleRate));
}




