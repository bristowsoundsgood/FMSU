//
// Created by Joe Bristow on 20/07/2026.
//

#include "AutoGain.h"

void AutoGain::readInput(const juce::AudioBuffer<float>& buffer, const int numSamples)
{
    // Get average of signal to avoid biasing one channel over another (autogain should affect both channels equally)
    const float rmsLHS = buffer.getRMSLevel(0, 0, numSamples);
    const float rmsRHS = buffer.getRMSLevel(1, 0, numSamples);

    _inRMS = (rmsLHS + rmsRHS) / 2.0f;
}

void AutoGain::readOutput(const juce::AudioBuffer<float>& buffer, const int numSamples)
{
    // combine signal to avoid bias
    const float rmsLHS = buffer.getRMSLevel(0, 0, numSamples);
    const float rmsRHS = buffer.getRMSLevel(1, 0, numSamples);

    _outRMS = (rmsLHS + rmsRHS) / 2.0f;
}

void AutoGain::applyGain(juce::AudioBuffer<float>& buffer, const int numSamples)
{
    const float ratio = _inRMS / _outRMS;

    _outRMS = 0.0f;
    _inRMS = 0.0f;

    buffer.applyGain(0, 0, numSamples, ratio);
    buffer.applyGain(1, 0, numSamples, ratio);

std::cout << "Applying gain with ratio: " << ratio << '\n';
}


