/*
  ==============================================================================

    EchoEffectProcessor.cpp
    Created: 17 Mar 2026 12:47:03pm
    Author:  eric.tarr

  ==============================================================================
*/

#include "EchoEffectProcessor.h"


void EchoEffectProcessor::prepareToPlay(float sampleRate){
    //delay.prepareToPlay(sampleRate);
    delay.setFs(sampleRate);
    delay.setSpeed(2.f); // LFO speed
    delay.setDepth(5.f); // LFO depth
    
    Fs = sampleRate;
    
}

void EchoEffectProcessor::setFeedbackGain(float feedbackGain){
    g = feedbackGain;
}

void EchoEffectProcessor::setDelayInMilliseconds(float delayMS){
    //delay.setDelayInMilliseconds(delayMS);
    float delaySamples = Fs * (delayMS / 1000.f);
    delay.setDelaySamples(delaySamples);
}

void EchoEffectProcessor::setWetPercentage(float wetPercent){
    wet = wetPercent / 100.f;
}

void EchoEffectProcessor::processBuffer(float * buffer, int c, int N){
    for (int n = 0; n < N; ++n){
        buffer[n] = processSample(buffer[n],c);
    }
}

float EchoEffectProcessor::processSample(float x, int c){
    
    float w = x + (v[c] * g);
    v[c] = delay.processSample(w, c);
    float y = wet * v[c] + (1.f-wet) * x;
    
    return y; 
    
}
