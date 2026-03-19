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

