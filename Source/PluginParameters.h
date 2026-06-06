//
// Created by Joe on 04/06/2026.
//

#ifndef SIMPLEJUCEPLUGINTEMPLATE_PLUGINPARAMETERS_H
#define SIMPLEJUCEPLUGINTEMPLATE_PLUGINPARAMETERS_H
#include <juce_audio_processors/juce_audio_processors.h>

namespace PluginConfig
{
    const juce::ParameterID attackParamID { "attack", 1 };
    const juce::String attackParamName { "attack" };
    constexpr float attackMin { 0.0f };
    constexpr float attackMax { 1.0f };
    constexpr float attackDefault { 0.0f };
    constexpr float attackStep { 0.01f };
    const juce::NormalisableRange attackRange { attackMin, attackMax, attackStep };

    const juce::ParameterID releaseParamID { "release", 1 };
    const juce::String releaseParamName { "release" };
    constexpr float releaseMin { 0.0f };
    constexpr float releaseMax { 1.0f };
    constexpr float releaseDefault { 0.0f };
    constexpr float releaseStep { 0.01f };
    const juce::NormalisableRange releaseRange { releaseMin, releaseMax, releaseStep };
}

class PluginParameters
{
public:
    PluginParameters(const juce::AudioProcessorValueTreeState& stateManager);
    float getAttack() const;
    float getSustain() const;

    static juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
private:
    juce::AudioParameterFloat* _attack;
    juce::AudioParameterFloat* _release;
};


#endif //SIMPLEJUCEPLUGINTEMPLATE_PLUGINPARAMETERS_H