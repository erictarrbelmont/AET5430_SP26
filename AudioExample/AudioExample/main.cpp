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


class MyAudioBuffer{
    
public:
 
    void fillBufferWithSamples(vector<float> & signal, int & signalIndex){
        int signalSize = signal.size();
        for (int n = 0; n < bufferSize; ++n){
            if (signalIndex < signalSize){
                samples[0][n] = signal[signalIndex];
                signalIndex++;
            }
            else {
                samples[0][n] = 0.f;
            }
        }
    }
    
    void setBufferSize(int b){
        bufferSize = b;
    }
    
    float getSample(int c, int n){
        return samples[c][n];
    }
    
private:
    static const int MAXBUFFERSIZE = 1024;
    static const int MAXNUMCHANNELS = 2;
    
    float samples[MAXNUMCHANNELS][MAXBUFFERSIZE];
    
    int bufferSize = 1024; // could change from "DAW"
    int numChannels = 1;
    
};


class GainEffect{
public:
    
    GainEffect(){
        dBAmp = 0.f;
        A = 1.f;
    }
    
    float dBAmp = 0.f; // decibel amplitude
    
    // Overloaded Constructor with initialization list
    GainEffect(float dBValue) : dBAmp(dBValue)
    {
        setdBAmp(dBValue);
    }
    
    // Destructor - optional, special function that's called when objects go out of scope
    ~GainEffect(){
        int test = 1;
    }
    
    void processSignal(vector<float> & signal, int N){
        for (int n = 0; n < N ; ++n){
            signal[n] = processSample(signal[n]);
        }
    }
    
    float processSample(float x){
        return x * A;
    }
    
    void setdBAmp(float dBValue){
        dBAmp = dBValue;
        A = pow(10.f,dBAmp/20.f);
    }
    
    
    float A = 1.f; // linear amplitude
};

class TremoloEffect
{
public:
    
    enum LFOType{
        SINE,
        SQUARE
    };
    
    void processSignal(vector<float> & signal, int N){
        for (int n = 0; n < N ; ++n){
            signal[n] = processSample(signal[n]);
        }
    }
    
    float processSample(float x){
        // Tremolo effect goes in here
        float lfo;
        if (type == 0){
            lfo = A * sin(phi) + mu;
        }
        else{
            //square
            if (phi < M_PI){
                lfo = 1.f;
            }
            else {
                lfo = A * -1.f + mu;
            }
            
        }
        float y = lfo * x;
        
        // Update current phase angle for next sample
        phi += phaseChange;
        
        if (phi > (2.f*M_PI)){
            phi -= 2.f*M_PI;
        }
        
        return y;
    }
    
    void setRate(float rate){
        freq = rate;
        phaseChange = freq * 2 * M_PI / Fs;
    }
    
    void setDepth(float d){
        depth = d; // 0-1
        A = depth * 0.5f;
        mu = 1.f - A;
    }
    
    void setType(LFOType t){
        // sine = true, square = false
        type = t;
    }
    
    void setFs(float sampleRate){
        Fs = sampleRate;
    }

private:
    float freq = 1.f; // frequency in Hz
    float depth = 1.f; // intensity of effect
    float Fs = 44100.f;
    
    float A = 0.5f; // LFO amplitude
    float mu = 0.5f; // DC Offset
    
    float phi = 0.f; // initial phase angle in radians
    float phaseChange = 0.1f; // change per 1 sample
    
    // Data type is the enum
    LFOType type = LFOType::SINE;
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
    
    MyAudioBuffer buffer;

    int signalIndex = 0;
    while (signalIndex < info.N){
        buffer.fillBufferWithSamples(signal, signalIndex);
        
        // Need to write this for effect
        //effect.processBuffer(buffer);
    }
    
    
//    {
//        GainEffect gain2;
//        gain2.setdBAmp(6.f);
//        gain2.processSignal(signal, info.N);
//    }
    
    
//    GainEffect gain {-18.f}; // constructor initialized to -18 dB
//    //gain.setdBAmp(-18.f);
//    gain.processSignal(signal,info.N);
    
    TremoloEffect effect;
    effect.setFs(info.Fs);
    effect.setRate(4.f);
    effect.setDepth(1.f);
    effect.setType(TremoloEffect::LFOType::SINE);
    effect.processSignal(signal, info.N);
    
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

