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
    
    
    button.setBounds(30,50,100,60); // x,y,w,h
    button.setButtonText("Bypass");
    addAndMakeVisible(button);
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
}

void MyEchoPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
}
