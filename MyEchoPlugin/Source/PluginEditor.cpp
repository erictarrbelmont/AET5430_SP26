/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MyEchoPluginAudioProcessorEditor::MyEchoPluginAudioProcessorEditor (MyEchoPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    
    bypassButton.addListener(this);
    bypassButton.setBounds(30,80,100,60); // x,y,w,h
    bypassButton.setButtonText("Bypass");
    addAndMakeVisible(bypassButton);
    
    buttonLabel.setText("My Button",juce::dontSendNotification);
    buttonLabel.attachToComponent(&bypassButton, false);
    
    wetDrySlider.addListener(this);
    wetDrySlider.setBounds(270, 50, 100, 100);
    wetDrySlider.setRange(0.f,100.f,1.f); // %
    wetDrySlider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, false, 50, 20);
    wetDrySlider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    
    addAndMakeVisible(wetDrySlider);
    
    distortionSelector.addListener(this);
    distortionSelector.setBounds(30, 225, 120, 50);
    distortionSelector.addItem("Soft Clip", 1);
    distortionSelector.addItem("Hard Clip", 2);
    distortionSelector.setText("Select type");
    addAndMakeVisible(distortionSelector);
    
    
    
}

MyEchoPluginAudioProcessorEditor::~MyEchoPluginAudioProcessorEditor()
{
}

//==============================================================================
void MyEchoPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    //g.fillAll(juce::Colours::white);

    g.setColour (juce::Colours::tomato);
    g.setFont (juce::FontOptions (30.0f));
    g.drawFittedText ("Echo Plugin", getLocalBounds(), juce::Justification::centred, 1);
    
    g.setColour (juce::Colours::tomato);
    g.setFont (juce::FontOptions (12.0f));
    g.drawFittedText ("Wet/Dry", 270,36,100,12, juce::Justification::centred, 1);
}

void MyEchoPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}

void MyEchoPluginAudioProcessorEditor::buttonClicked(juce::Button *button){
    
    if (button == &bypassButton){
        bool bypassState = button->getToggleState();
        audioProcessor.isBypassed = bypassState; 
    }
    //if (button == &syncButton){
    //
    //}
}

void MyEchoPluginAudioProcessorEditor::sliderValueChanged(juce::Slider *slider){
    
    if (slider == &wetDrySlider){
        float value = slider->getValue();
        audioProcessor.wetValue = value;
    }
    
}

void MyEchoPluginAudioProcessorEditor::comboBoxChanged(juce::ComboBox *comboBox){
    
    if (comboBox == &distortionSelector){
        int id = comboBox->getSelectedId();
        audioProcessor.distortionSelection = id;
    }
    
}
