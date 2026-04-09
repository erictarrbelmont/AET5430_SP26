//
//  main.cpp
//  AudioExample
//
//  Created by Hack Audio on 10/5/19.
//  Copyright © 2019 Eric Tarr. All rights reserved.
//

#include <iostream>
#include <cmath>
#include "AudioFile/AudioFile.hpp"
#include "AudioFile/Sound.hpp"
using namespace std;

// User created structure
struct AudioInfo {
    string filename;
    int Fs;
    int bitDepth;
    int numChannels;
    int N;
};

void audioread(AudioInfo & info, vector<float> & signal){
    
    audioread(info.filename, signal, info.Fs, info.bitDepth, info.numChannels);
    
}


class AudioEffectProcessor {
  // Generic "base" class
  // Include functions and variables
  // that show up in all audio effect classes
public:
    
    void prepareToPlay(float sampleRate){
        Fs = sampleRate;
    }
    
    void processBuffer(vector<float> & buffer, int c, int N){
        for (int n = 0; n < N; ++n){
            buffer[n] = processSample(buffer[n],c);
        }
    }
    
    //virtual float processSample(float x, int c){
    //    return x;
    //}
    
    // PURE Virtual Function
    virtual float processSample(float x, int c) = 0;

private:
    
    float Fs;
    
};

class MySimpleClass {
public:
    
    MySimpleClass(int i){
        j = i;
    }
    
private:
    int j;
};


class GainEffectProcessor : public AudioEffectProcessor
{
    // Specific "derived" class
public:
    
    GainEffectProcessor(int i,int i1, int i2) : msc(i), msc1(i1), msc2(i2)
    {
        
    }
    
    void setLinearGain(float gain){
        g = gain;
    }
    
    float processSample(float x, int c) override {
        return x * g;
    }
    
private:
    float g = 1.f;
    
    MySimpleClass msc;
    MySimpleClass msc1;
    MySimpleClass msc2;
};





int main() {
    
    AudioInfo info;
    info.filename = "AcGtr.wav";
    
    vector<float> signal;
    
    audioread(info,signal);
    
    
    
    //sound(signal,Fs,bitDepth,numChannels);
    
    // For stereo, get size of one of the channels
    if (info.numChannels == 1){
        info.N = signal.size();
    }
    else{
        //info.N = signal[0].size();
    }
    
    
    
    //sound(signal, info.Fs, info.bitDepth, info.numChannels);
    
    
    //myGainFunction(signal, info.N, -18.f);
    
    
    vector<float> monoSignal;
    
    AudioInfo monoInfo;
    monoInfo.filename = "AcGtr.wav";
    audioread(monoInfo.filename,
              monoSignal,
              monoInfo.Fs,
              monoInfo.bitDepth,
              monoInfo.numChannels);
    
    GainEffectProcessor effect {7};
    
    effect.prepareToPlay(monoInfo.Fs);
    effect.setLinearGain(0.5f);
    effect.processBuffer(monoSignal, 0, signal.size());
    
    
    string outputFilename = "myOutputFile.wav";
    
    audiowrite(outputFilename, signal, info.Fs, info.bitDepth, info.numChannels);
    
    return 0;
}

