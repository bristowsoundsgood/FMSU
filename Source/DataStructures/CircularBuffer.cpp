//
// Created by Joe Bristow on 05/08/2026.
//

#include "CircularBuffer.h"

#include <iostream>


void CircularBuffer::resize(const size_t bufferSize)
{
    _buffer.resize(bufferSize, 0.0f);
}

void CircularBuffer::setSample(size_t index, const float value)
{
    _buffer[index % _buffer.size()] = value;
}

float CircularBuffer::getSample(const size_t index) const
{
    const size_t bufferSize = _buffer.size();
    return _buffer[index % bufferSize];
}

size_t CircularBuffer::getSize() const
{
    return _buffer.size();
}
