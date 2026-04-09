/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MyEchoPluginAudioProcessor::MyEchoPluginAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ) , apvts(*this,nullptr,"Params",createParams())
#endif
{
}

juce::AudioProcessorValueTreeState::ParameterLayout MyEchoPluginAudioProcessor::createParams(){
    
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    
    // Add our sliders to params
    params.push_back(std::make_unique<juce::AudioParameterFloat> (juce::ParameterID({"Wet",1}),"Dry/Wet",0.f,100.f,50.f));
    
    // Add our buttons to params
    params.push_back(std::make_unique<juce::AudioParameterBool> (juce::ParameterID({"Bypass",1}),"Bypass",false));
    
    // Add out ComboBox
    params.push_back(std::make_unique<juce::AudioParameterInt>(juce::ParameterID({"DistortionSelect",1}), "Distortion Type", 1, 2, 1));
    
    return {params.begin(),params.end()};
}


MyEchoPluginAudioProcessor::~MyEchoPluginAudioProcessor()
{
}

//==============================================================================
const juce::String MyEchoPluginAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MyEchoPluginAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MyEchoPluginAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MyEchoPluginAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MyEchoPluginAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MyEchoPluginAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MyEchoPluginAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MyEchoPluginAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MyEchoPluginAudioProcessor::getProgramName (int index)
{
    return {};
}

void MyEchoPluginAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MyEchoPluginAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    echo.prepareToPlay(sampleRate);
    echo.setDelayInMilliseconds(300.f);
}

void MyEchoPluginAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MyEchoPluginAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MyEchoPluginAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    
    if (isBypassed)
        return;
    
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    
    echo.setWetPercentage(wetValue);
    echo.setFeedbackGain(0.0f);
    
    int N = buffer.getNumSamples();
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        echo.processBuffer(channelData, channel, N);
        
        if (distortionSelection == 1){
            // arctan
        }
        else {
            // cubic
        }
    }
}

//==============================================================================
bool MyEchoPluginAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MyEchoPluginAudioProcessor::createEditor()
{
    return new MyEchoPluginAudioProcessorEditor (*this);
}

//==============================================================================
void MyEchoPluginAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    
    auto currentState = apvts.copyState();
    
    std::unique_ptr<juce::XmlElement> xml (currentState.createXml());
    
    copyXmlToBinary(*xml, destData);
    
}

void MyEchoPluginAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MyEchoPluginAudioProcessor();
}
