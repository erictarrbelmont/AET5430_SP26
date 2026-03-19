/*
  ==============================================================================

    EchoEffectProcessor.cpp
    Created: 17 Mar 2026 12:47:03pm
    Author:  eric.tarr

  ==============================================================================
*/

#include "EchoEffectProcessor.h"


void EchoEffectProcessor::prepareToPlay(float sampleRate){
    delay.prepareToPlay(sampleRate);
    Fs = sampleRate;
}

void EchoEffectProcessor::setDelayInMilliseconds(float delayMS){
    delay.setDelayInMilliseconds(delayMS);
}

void EchoEffectProcessor::processBuffer(float * buffer, int c, int N){
    for (int n = 0; n < N; ++n){
        buffer[n] = processSample(buffer[n],c);
    }
}

float EchoEffectProcessor::processSample(float x, int c){
    
    float v = delay.processSample(x, c);
    float y = v + x;
    
    return y; 
    
}
