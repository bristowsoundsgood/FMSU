//
// Created by Joe on 29/05/2026.
//

#ifndef FMSU_ENVELOPE1_H
#define FMSU_ENVELOPE1_H


class EnvelopeFollower
{
public:
    void prepare(float sampleRate);
    float process(float sample);

    void setAttack(float milliseconds);
    void setSustain(float milliseconds);

    float convertToScale(float milliseconds);

private:

    // 'Attack' and 'Sustain' are multipliers that scale the transient/body of a signal, respectively.
    float _attack {0.0f};
    float _sustain {0.0f};

    float _envelope {0.0f};
    float _sampleRate {0.0f};
};


#endif //FMSU_ENVELOPE1_H