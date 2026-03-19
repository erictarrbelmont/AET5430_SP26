/*
  ==============================================================================

    DelayEffectProcessor.cpp
    Created: 17 Mar 2026 12:47:19pm
    Author:  eric.tarr

  ==============================================================================
*/

#include "DelayEffectProcessor.h"

void DelayEffectProcessor::prepareToPlay(float sampleRate){
    
    Fs = sampleRate;
    d = Fs; // initialize to 1 second of delay
    
    wi[0] = MAXDELAYSAMPLES - 1;
    wi[1] = wi[0];
    
    ri[0] = wi[0] - d;
    ri[1] = ri[0];
    
}

void DelayEffectProcessor::setDelayInMilliseconds(float delayMS){
    float delaySec = delayMS / 1000.f;
    d = floor(delaySec * Fs);
    
    wi[0] = MAXDELAYSAMPLES - 1;
    wi[1] = wi[0];
    
    ri[0] = wi[0] - d;
    ri[1] = ri[0];
}

void DelayEffectProcessor::processBuffer(float * buffer, int c, int N){
    for (int n = 0; n < N ; ++n){
        buffer[n] = processSample(buffer[n],c);
    }
}

float DelayEffectProcessor::processSample(float x, int c){
    
    // write into delayBuffer
    int index = wi[c];
    delayBuffer[index][c] = x;
    
    // read out of delayBuffer
    index = ri[c];
    x = delayBuffer[index][c];
    
    wi[c]++; // increment write pointer
    if (wi[c] >= MAXDELAYSAMPLES){
        wi[c] = 0;
    }
    
    ri[c]++; // increment read pointer
    if (ri[c] >= MAXDELAYSAMPLES){
        ri[c] = 0;
    }
    
    return x;
}

