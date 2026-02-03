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


int main() {
    
    string filename = "AcGtr.wav";
    vector<float> signal;
    int Fs;
    int bitDepth;
    int numChannels;
    

    audioread(filename, signal, Fs, bitDepth, numChannels);
    
    sound(signal,Fs,bitDepth,numChannels);
    
    int N = signal.size();
    
    //int * p; // declare pointer
    //p = &N;
    
    //int M = (*p) + 1; // de-reference "p" + 1
    
    vector<float> * mainP = &signal; // memory address of signal in main
    
    myGainFunction(signal, N, -18.f);
    
    float myArray[5] = {1.f,2.f,3.f,4.f,5.f};
    
    myArrayFunction(myArray, 5);
    
    string outputFilename = "myOutputFile.wav";
    
    audiowrite(outputFilename, signal, Fs, bitDepth, numChannels);
    
    return 0;
}

