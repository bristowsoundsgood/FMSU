//
// Created by Joe on 04/06/2026.
//

#include "PluginParameters.h"

PluginParameters::PluginParameters(const juce::AudioProcessorValueTreeState& stateManager)
{
    _attack = dynamic_cast<juce::AudioParameterFloat*>(stateManager.getParameter(PluginConfig::attackParamID.getParamID()));
    _release = dynamic_cast<juce::AudioParameterFloat*>(stateManager.getParameter(PluginConfig::releaseParamID.getParamID()));
}

juce::AudioProcessorValueTreeState::ParameterLayout PluginParameters::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout {};

    layout.add(
        std::make_unique<juce::AudioParameterFloat>(PluginConfig::attackParamID.getParamID(), PluginConfig::attackParamName,
                            PluginConfig::attackRange, PluginConfig::attackDefault),

        std::make_unique<juce::AudioParameterFloat>(PluginConfig::releaseParamID.getParamID(), PluginConfig::releaseParamName,
                           PluginConfig::releaseRange, PluginConfig::releaseDefault)
    );

    return layout;
}

float PluginParameters::getAttack() const
{
    return _attack->get();
}

float PluginParameters::getSustain() const
{
    return _release->get();
}



