//
// Created by Joe on 04/06/2026.
//

#include "PluginParameters.h"

PluginParameters::PluginParameters(const juce::AudioProcessorValueTreeState& stateManager)
{
    _attack = dynamic_cast<juce::AudioParameterFloat*>(stateManager.getParameter(PluginConfig::attackParamID.getParamID()));
    _sustain = dynamic_cast<juce::AudioParameterFloat*>(stateManager.getParameter(PluginConfig::sustainParamID.getParamID()));
    _softClipGain = dynamic_cast<juce::AudioParameterFloat*>(stateManager.getParameter(PluginConfig::softClipGainParamID.getParamID()));
    _filterCutoff = dynamic_cast<juce::AudioParameterFloat*>(stateManager.getParameter("filterCutoff"));
    _widthCoefficient = dynamic_cast<juce::AudioParameterFloat*>(stateManager.getParameter(PluginConfig::widthParamID.getParamID()));
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
                          PluginConfig::softClipGainRange, PluginConfig::softClipGainDefault),

        std::make_unique<juce::AudioParameterFloat>(PluginConfig::widthParamID.getParamID(), PluginConfig::widthParamName,
                        PluginConfig::widthRange, PluginConfig::widthDefault),

        std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("filterCutoff", 1), "filterCutoff",
                        juce::NormalisableRange(20.0f, 20000.0f, 1.0f), 2000.0f)
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

float PluginParameters::getFilterCutoff() const
{
    return _filterCutoff->get();
}

float PluginParameters::getWidthCoefficient() const
{
    return _widthCoefficient->get();
}



