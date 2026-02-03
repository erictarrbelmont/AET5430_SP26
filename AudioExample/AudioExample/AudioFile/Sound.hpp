//
// Sound.hpp
//
// Simulates MATLAB 'sound' function for audio playback
// to sound card
//
// Requires AudioTooolbox and CoreFoundation frameworks
//
// Created 1/28/2026
//
// © 2026 Jack Travis Dunn. All rights reserved.

#pragma once

#include <iostream>
#include <cmath>
#include "AudioToolbox/AudioToolbox.h"

using namespace std;

template <typename T>
int sound (vector<vector<T>>& signal, const int& Fs, const int& bitDepth, const int& numChannels);

template <typename T>
int sound (vector<T>& signal, const int& Fs, const int& bitDepth, const int& numChannels);

template <typename T>
void callback (void* ptr, AudioQueueRef queue, AudioQueueBufferRef bufferRef);

template <typename T>
/**
@struct SignalInfo
 
@field sampleIndex - Index of the next sample to be processed
@field signalLength - Size of the signal
@field numChannels - Number of channels in the signal
@field pSignal - Pointer to the actual sample data

*/
struct SignalInfo {
	uint64_t sampleIndex;
	uint64_t signalLength;
	int numChannels;
	vector<vector<T>>* pSignal;
};

/**
@function sound

@brief Simulates MATLAB 'sound' function by playing a vector of vectors of samples to the sound card

Template argument:
@template T - the data type of the source signal samples

Arguments:
@param signal - vector of a vector of float samples, one vector for each channel
@param Fs - sample rate of the signal
@param bitDepth - bit depth of the signal
@param numChannels - number of channels in the signal

*/
template <typename T>
int sound (vector<vector<T>>& signal, const int& Fs, const int& bitDepth, const int& numChannels)
{
	// Size of buffers used to present audio to the playback queue
	// Adjust to suit performance considerations
	const int BUFFER_SIZE = 512;
	
	// Specify the number of buffers to create. Each buffer is rotated in order so
	// that as one is loaded with playback data, the others are queued for, or
	// are actively in the process of, playback
	// Adjust to suit for performance and smoothness of playback
	const int NUM_BUFFERS = 3;

	// Array of references to AudioQueueBuffer objects
	AudioQueueBufferRef buffers[NUM_BUFFERS];

	// A pointer to the AudioQueue
	AudioQueueRef queue;

	// A generic system return value
	OSStatus status;
	
	// Initialize an empty AudioStreamBasicDescription struct
	AudioStreamBasicDescription fmt = { 0 };
		
	// Create a SignalInfo struct with information about our signal, and a
	// pointer to the signal vector
	uint64_t signalLength = signal[0].size();
	SignalInfo<T> info {0, signalLength, numChannels, &signal};

	// Actual size of the buffer data in bytes
	int dataByteSize = BUFFER_SIZE * sizeof(int16_t) * numChannels;

	// Initialize the AudioStreamBasicDescription struct fields
	// Passed-in sample rate
	fmt.mSampleRate = Fs;
	// WAV audio is linear PCM
	fmt.mFormatID = kAudioFormatLinearPCM;
	// We will supply signed integer values
	fmt.mFormatFlags = kAudioFormatFlagIsSignedInteger;
	// For CoreAudio, a frame is one set of time-contiguous samples
	fmt.mFramesPerPacket = 1;
	// Passed-in number of channels
	fmt.mChannelsPerFrame = numChannels;
	// For CoreAudio, a frame is one set of time-contiguous samples
	fmt.mBytesPerPacket = fmt.mBytesPerFrame = sizeof(int16_t) * numChannels;
	// Passed-in bit depth
	fmt.mBitsPerChannel = bitDepth;

	// Create a new AudioQueue object, specifying format info, the callback for the
	// system to reference, and our user-defined struct with the signal
	status = AudioQueueNewOutput(&fmt, callback<T>, &info, CFRunLoopGetCurrent(),
			   kCFRunLoopCommonModes, 0, &queue);

	if (status == kAudioFormatUnsupportedDataFormatError) return status;

	// Set up buffers
	for (int n = 0; n < NUM_BUFFERS; n++) {

		// Allocate an audio buffer, specifying its size, and get a reference to it
		status = AudioQueueAllocateBuffer (queue, dataByteSize, &buffers[n]);

		// Get the actual pointer to the AudioQueueBuffer from the reference
		AudioQueueBuffer* buf = buffers[n];

		// Set its size in bytes
		buf->mAudioDataByteSize = dataByteSize;

		// Calling this directly "primes the pump" in terms of getting data loaded
		// into the buffer for processing
		callback<T> (&info, queue, buffers[n]);

	}
	
	// Set the volume to max
	status = AudioQueueSetParameter (queue, kAudioQueueParam_Volume, 1.0);

	// Start the queue
	status = AudioQueueStart (queue, NULL);

	// Process while we haven't reached the end
	while (info.sampleIndex < info.signalLength)
		CFRunLoopRunInMode (
		   kCFRunLoopDefaultMode,
		   0.25, // seconds
		   false // don't return after source handled
		);

	return 0;
}

/**
@function sound

@brief Simulates MATLAB 'sound' function by playing a mono vector of samples to the sound card
Accomplished by wrapping multichannel version with mono signal signature

Template argument:
@template T - the data type of the source signal samples

Arguments:
@param signal - vector of a vector of float samples, one vector for each channel
@param Fs - sample rate of the signal
@param bitDepth - bit depth of the signal
@param numChannels - number of channels in the signal

*/
template <typename T>
int sound (vector<T>& signal, const int& Fs, const int& bitDepth, const int& numChannels)
{
	vector<vector<T>> newSignal;
	newSignal.push_back(signal);
	
	return sound(newSignal, Fs, bitDepth, numChannels);

}


/**
@function callback
 
@brief Function that CoreAudio calls periodically as our audio is played. It is incumbent
on us to fill mAudioData field of bufferRef with our sample data. ptr is a pointer
to the SignalInfo struct we specified in the initial call to AudioQueueNewOutput. It
contains the original signal data, its size, and a running index of where we are in
processing the samples. We will enqueue our data in queue when it is full

Template argument:
@template T - the data type of the source signal samples
 
Arguments:
@param ptr - pointer to the SignalInfo struct
@param queue - pointer to the audio queue
@param bufferRef - pointer to the destination buffer

*/
template <typename T>
void callback (void* ptr, AudioQueueRef queue, AudioQueueBufferRef bufferRef)
{
	// Generic system return variable
	OSStatus status;
	
	// The ptr parameter is a pointer to the SignalInfo struct we passed in when we
	// created the queue
	SignalInfo<T>* info = (SignalInfo<T>*)ptr;
	
	// Get the actual pointer to the AudioQueueBuffer from the reference
	AudioQueueBuffer* buffer = bufferRef;
	
	// Get the number of channels from the struct
	int numChannels = info->numChannels;
	
	// The number of samples is the size of the buffer in bytes divided by the size of
	// int16_t multiplied by the number of channels. Get the size in bytes from the buffer
	int N = buffer->mAudioDataByteSize / (sizeof(int16_t) * numChannels);
	
	// Get the destination samples we're working with
	int16_t* outSamples = (int16_t*)buffer->mAudioData;
	
	// Get a pointer to the signal samples we're going to process
	vector<vector<T>> signal = *(info->pSignal);
	
	// Get the offset into the signal where we are starting
	uint64_t startSampleIndex = info->sampleIndex;
	
	// Traverse the length of the destination buffer
	for (int i = 0; i < N; i++) {
		
		// Don't overrun the end of the signal
		if (info->sampleIndex < info->signalLength) {
			
			// Iterate across however many channels are in the signal
			for (int channel = 0; channel < numChannels; channel++) {
				
				// Calculate an offset from where we started in the signal for
				// the current buffer
				uint64_t sampleIndexDiff = info->sampleIndex - startSampleIndex;
				
				// Convert the float value into int16
				int currentSample = signal[channel][info->sampleIndex]*32767;
				
				// Put the current sample into the destination. Channels are
				// interleaved in the buffer a la L0R0L1R1L2R2L3R3
				outSamples[(numChannels * sampleIndexDiff) + channel] = currentSample;
				
			}

		}

		// Increment the index into the signal
		info->sampleIndex++;

	}
	
	// Enqueue the data we just filled
	status = AudioQueueEnqueueBuffer (queue, bufferRef, 0, NULL);
	
	// If we've reached the end of the signal...
	if (info->sampleIndex == info->signalLength) {
		//...flush the queue...
		AudioQueueFlush(queue);
		//...and stop it
		AudioQueueStop(queue, false);
		// Free resources
		AudioQueueDispose(queue, false);
	}

	
}
