/*
  ==============================================================================

    EchoEffectProcessor.h
    Created: 17 Mar 2026 12:47:03pm
    Author:  eric.tarr

  ==============================================================================
*/

#pragma once

#include "DelayEffectProcessor.h"


class EchoEffectProcessor {
  
    public:
    
    void prepareToPlay(float sampleRate);
    
    void setDelayInMilliseconds(float delayMS);
    
    void setWetPercentage(float wetPercent);
    
    void setFeedbackGain(float feedbackGain);
    
    void processBuffer(float * buffer, int c, int N);
    
    float processSample(float x, int c);
    
    private:
    
    DelayEffectProcessor delay;
    
    float Fs;
    
    float wet = 0.f;
    
    float g = 0.f; // linear gain
    
    float v[2] = {0.f};
    
};
