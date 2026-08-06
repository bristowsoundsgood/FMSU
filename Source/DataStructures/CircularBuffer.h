//
// Created by Joe Bristow on 05/08/2026.
//

#ifndef FMSU_CIRCULARBUFFER_H
#define FMSU_CIRCULARBUFFER_H
#include <vector>

/**
 * When i exceeds buffer.size, wrap back around
 */

class CircularBuffer
{
public:
    void resize(size_t bufferSize);
    void setSample(size_t index, float value);
    [[nodiscard]] float getSample(size_t index) const;
    [[nodiscard]] size_t getSize() const;
private:
    std::vector<float> _buffer {};
};


#endif //FMSU_CIRCULARBUFFER_H
