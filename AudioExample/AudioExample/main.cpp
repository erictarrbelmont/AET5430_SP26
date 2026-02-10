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



void myGainFunction(vector<vector<float>> & sig, int N, float dBAmp){
    
    float A = powf(10.f,dBAmp/20.f); // A - linear amplitude
    
    // Stereo processing
    for (int c = 0; c < 2; ++c){
        for (int n = 0; n < N; ++n){
            sig[c][n] *= A;
        }
    }
}

void myGainFunction(vector<float> & sig, int N, float dBAmp){
    vector<float> * functionP = &sig; // memory address of signal in function
    
    float A = powf(10.f,dBAmp/20.f); // A - linear amplitude
    for (int n = 0; n < N; ++n){
        sig[n] *= A;
    }
    
}

void myArrayFunction(float * array, int N){
    
    for (int n = 0; n < N; ++n){
        //array[n] = n+10;
        *(array++) = n+10;
    }
    
}



class GainEffect{
public:
    
    GainEffect(){
        dBAmp = 0.f;
        A = 1.f;
    }
    
    float dBAmp = 0.f; // decibel amplitude
    
    // Overloaded Constructor
    GainEffect(float dBValue){
        setdBAmp(dBValue);
    }
    

    
    void processSignal(vector<float> & signal, int N){
        for (int n = 0; n < N ; ++n){
            signal[n] = processSample(signal[n]);
        }
    }
    
    float processSample(float x){
        return x * A;
    }nike.
    
    void setdBAmp(float dBValue){
        dBAmp = dBValue;
        A = pow(10.f,dBAmp/20.f);
    }
    
    
    float A = 1.f; // linear amplitude
};

int main() {
    
    AudioInfo info;
    info.filename = "AcGtr.wav";
    
    vector<float> signal;
    
    audioread(info,signal);
    
    // OLD WAY without structure
    //audioread(info.filename, signal, info.Fs, info.bitDepth, info.numChannels);
    
    
    
    //sound(signal,Fs,bitDepth,numChannels);
    
    // For stereo, get size of one of the channels
    if (info.numChannels == 1){
        info.N = signal.size();
    }
    else{
        //info.N = signal[0].size();
    }
    
    GainEffect gain2;
    gain2.setdBAmp(6.f);
    gain2.processSignal(signal, info.N);
    
    
    
    GainEffect gain {-18.f}; // constructor initialized to -18 dB
    //gain.setdBAmp(-18.f);
    gain.processSignal(signal,info.N);
    
    sound(signal, info.Fs, info.bitDepth, info.numChannels);
    
    
    //myGainFunction(signal, info.N, -18.f);
    
    
    vector<float> monoSignal;
    
    AudioInfo monoInfo;
    monoInfo.filename = "AcGtr.wav";
    audioread(monoInfo.filename,
              monoSignal,
              monoInfo.Fs,
              monoInfo.bitDepth,
              monoInfo.numChannels);
    
    
    string outputFilename = "myOutputFile.wav";
    
    audiowrite(outputFilename, signal, info.Fs, info.bitDepth, info.numChannels);
    
    return 0;
}

