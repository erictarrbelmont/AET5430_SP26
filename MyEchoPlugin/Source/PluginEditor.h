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
class MyEchoPluginAudioProcessorEditor  : public juce::AudioProcessorEditor,
                        public juce::Button::Listener,
                        public juce::Slider::Listener,
                        public juce::ComboBox::Listener
{
public:
    MyEchoPluginAudioProcessorEditor (MyEchoPluginAudioProcessor&);
    ~MyEchoPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void buttonClicked(juce::Button * button) override;
    void sliderValueChanged(juce::Slider * slider) override;
    void comboBoxChanged(juce::ComboBox * comboBox) override;

private:
    
    juce::ToggleButton bypassButton;
    //juce::ToggleButton syncButton;
    
    juce::Slider wetDrySlider;
    
    juce::Label buttonLabel;
    
    juce::ComboBox distortionSelector;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MyEchoPluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MyEchoPluginAudioProcessorEditor)
};
