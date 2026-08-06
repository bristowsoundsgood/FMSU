//
// Created by Joe Bristow on 05/08/2026.
//

#ifndef FMSU_NOISEGENERATOR_H
#define FMSU_NOISEGENERATOR_H

#include "../DataStructures/CircularBuffer.h"
#include <random>
#include <iostream>

/**
 * Every .prepare() generates a large buffer of samples, tunable for size (min and max)
 * .get returns a random index
 */

class NoiseGenerator
{
public:
    void generateNoiseSamples(size_t numSamples);
    [[nodiscard]] float getRandomSample() const;
    [[nodiscard]] size_t getSize() const;
private:
    CircularBuffer _buffer {};
};


#endif //FMSU_NOISEGENERATOR_H
