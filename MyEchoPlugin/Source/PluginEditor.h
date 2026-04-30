/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class MyEchoPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MyEchoPluginAudioProcessorEditor (MyEchoPluginAudioProcessor&);
    ~MyEchoPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    using ButtonAttachment = juce::AudioProcessorValueTreeState::ButtonAttachment;
    
    using ComboBoxAttachment = juce::AudioProcessorValueTreeState::ComboBoxAttachment;
    
private:
    
    juce::ToggleButton bypassButton;
    //juce::ToggleButton syncButton;
    
    juce::Slider wetDrySlider;
    
    juce::Label buttonLabel;
    
    juce::ComboBox distortionSelector;
    
    std::vector<std::unique_ptr<SliderAttachment>> sliderAttachments;
    
    std::vector<std::unique_ptr<ButtonAttachment>> buttonAttachments;
    
    std::vector<std::unique_ptr<ComboBoxAttachment>> comboBoxAttachments;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MyEchoPluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyEchoPluginAudioProcessorEditor)
};
