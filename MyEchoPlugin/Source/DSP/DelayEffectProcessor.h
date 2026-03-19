/*
  ==============================================================================

    DelayEffectProcessor.h
    Created: 17 Mar 2026 12:47:19pm
    Author:  eric.tarr

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class DelayEffectProcessor
{
    public:
    
    void prepareToPlay(float sampleRate);
    
    void setDelayInMilliseconds(float delayMS);
    
    void processBuffer(float * buffer, int c, int N);
    
    float processSample(float x, int c);
    
    
    private:
    
    float Fs = 44100.f;
    
    int d = 192000; // delay in samples
    
    static const int MAXDELAYSAMPLES = 192000;
    
    float delayBuffer[MAXDELAYSAMPLES][2] = {0.f};
    
    int wi[2] = {MAXDELAYSAMPLES - 1};
    int ri[2] = {0};
    
};
