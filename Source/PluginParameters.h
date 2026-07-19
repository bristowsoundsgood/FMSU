//
// Created by Joe on 04/06/2026.
//

#ifndef SIMPLEJUCEPLUGINTEMPLATE_PLUGINPARAMETERS_H
#define SIMPLEJUCEPLUGINTEMPLATE_PLUGINPARAMETERS_H
#include <juce_audio_processors/juce_audio_processors.h>

namespace PluginConfig
{
    constexpr float defaultStep { 0.01f };

    // Min/max values are fine-tuned by ear to prevent artifacts from extreme values.
    const juce::ParameterID attackParamID { "attack", 1 };
    const juce::String attackParamName { "Attack" };
    constexpr float attackMin { 0.0f };
    constexpr float attackMax { 5.0f };
    constexpr float attackDefault { 0.0f };
    const juce::NormalisableRange attackRange { attackMin, attackMax, defaultStep };

    const juce::ParameterID sustainParamID { "sustain", 1 };
    const juce::String sustainParamName { "Sustain" };
    constexpr float sustainMin { -1.5f };
    constexpr float sustainMax { 0.0f };
    constexpr float sustainDefault { 0.0f };
    constexpr float sustainStep { 0.001f };
    const juce::NormalisableRange sustainRange { sustainMin, sustainMax, defaultStep };

    const juce::ParameterID softClipGainParamID { "softClipGain", 1 };
    const juce::String softClipGainParamName { "Soft Clip Gain" };
    constexpr float softClipGainMin { -24.0f };
    constexpr float softClipGainMax { 24.0f };
    constexpr float softClipGainDefault { 0.0f };
    constexpr float softClipGainStep { 0.01f };
    const juce::NormalisableRange softClipGainRange { softClipGainMin, softClipGainMax, defaultStep };
}

class PluginParameters
{
public:
    PluginParameters(const juce::AudioProcessorValueTreeState& stateManager);
    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    float getAttack() const;
    float getSustain() const;
    float getSoftClipGain() const;

private:
    juce::AudioParameterFloat* _attack;
    juce::AudioParameterFloat* _sustain;
    juce::AudioParameterFloat* _softClipGain;
};


#endif //SIMPLEJUCEPLUGINTEMPLATE_PLUGINPARAMETERS_H