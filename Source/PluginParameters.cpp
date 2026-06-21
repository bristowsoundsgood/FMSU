//
// Created by Joe on 04/06/2026.
//

#include "PluginParameters.h"

PluginParameters::PluginParameters(const juce::AudioProcessorValueTreeState& stateManager)
{
    _attack = dynamic_cast<juce::AudioParameterFloat*>(stateManager.getParameter(PluginConfig::attackParamID.getParamID()));
    _sustain = dynamic_cast<juce::AudioParameterFloat*>(stateManager.getParameter(PluginConfig::sustainParamID.getParamID()));
    _softClipGain = dynamic_cast<juce::AudioParameterFloat*>(stateManager.getParameter(PluginConfig::softClipGainParamID.getParamID()));
}

juce::AudioProcessorValueTreeState::ParameterLayout PluginParameters::createParameterLayout()
{
    juce::AudioProcessorValueTreeState::ParameterLayout layout {};

    layout.add(
        std::make_unique<juce::AudioParameterFloat>(PluginConfig::attackParamID.getParamID(), PluginConfig::attackParamName,
                            PluginConfig::attackRange, PluginConfig::attackDefault),

        std::make_unique<juce::AudioParameterFloat>(PluginConfig::sustainParamID.getParamID(), PluginConfig::sustainParamName,
                           PluginConfig::sustainRange, PluginConfig::sustainDefault),

        std::make_unique<juce::AudioParameterFloat>(PluginConfig::softClipGainParamID.getParamID(), PluginConfig::softClipGainParamName,
                          PluginConfig::softClipGainRange, PluginConfig::softClipGainDefault)
    );

    return layout;
}

float PluginParameters::getAttack() const
{
    return _attack->get();
}

float PluginParameters::getSustain() const
{
    return _sustain->get();
}

float PluginParameters::getSoftClipGain() const
{
    return _softClipGain->get();
}




