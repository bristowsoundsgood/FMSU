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

void EnvelopeFollower::setAttack(const float ms)
{
    _attack = _convertToScalarMultiplier(ms);
}

void EnvelopeFollower::setRelease(const float ms)
{
    _release = _convertToScalarMultiplier(ms);
}

float EnvelopeFollower::_convertToScalarMultiplier(const float milliseconds) const
{
    return std::pow(0.01f, 1.0f / (milliseconds * _sampleRate * 0.001f));
}

float EnvelopeFollower::getAttack() const
{
    return _attack;
}

float EnvelopeFollower::getRelease() const
{
    return _release;
}
