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
    
    void setLinearGain(float gain){
        g = gain;
    }
    
    float processSample(float x, int c) override {
        return x * g;
    }
    
private:
    float g = 1.f;
    
};





int main() {
    
    {
        // Stack pointer
        int i = 1;
        int * pInt;
        pInt = &i;
        
        // Heap pointer
        int * pInt2 = new int(1);
        
        delete pInt2;
        pInt2 = nullptr;
        int test = 1;
        
        std::unique_ptr<int> pInt3 = make_unique<int>(1);
        
        // Cannot be copied
        // std::unique_ptr<int> pInt4 = pInt3; //doesn't work
        std::unique_ptr<int> pInt4 = std::move(pInt3);
        
        
        std::shared_ptr<int> p5 = make_shared<int>(1);
        std::shared_ptr<int> p6 = p5;
    }
    
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
    
    GainEffectProcessor effect;
    
    effect.prepareToPlay(monoInfo.Fs);
    effect.setLinearGain(0.5f);
    effect.processBuffer(monoSignal, 0, signal.size());
    
    
    string outputFilename = "myOutputFile.wav";
    
    audiowrite(outputFilename, signal, info.Fs, info.bitDepth, info.numChannels);
    
    return 0;
}

