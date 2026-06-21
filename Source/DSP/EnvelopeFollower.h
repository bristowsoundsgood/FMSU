//
// Created by Joe on 29/05/2026.
//

#ifndef FMSU_ENVELOPE1_H
#define FMSU_ENVELOPE1_H

// https://www.musicdsp.org/en/latest/Filters/265-output-limiter-using-envelope-follower-in-c.html

class EnvelopeFollower
{
public:
    EnvelopeFollower();
    void prepare(float sampleRate);
    float process(float sample);

    void setAttack(float milliseconds);
    void setRelease(float milliseconds);

private:
    float _envelope {};
    float _attack {};
    float _release {};
    float _sampleRate {};

    [[nodiscard]] float _convertToScalarMultiplier(float milliseconds) const;
};


#endif //FMSU_ENVELOPE1_H