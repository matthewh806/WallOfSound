//
//  main.cpp
//  WallOfSound
//
//  Created by Matthew on 11/09/2018.
//  Copyright © 2018 Matthew. All rights reserved.
//

#include <iostream>
#include <vector>
#include "RtAudio.h"
#include "Oscillator.hpp"
#include "Envelope.hpp"
#include "AudioSettings.hpp"

Oscillator myOsc, counter;
Envelope myEnv;

int currentCount;

void setup()
{
    
}

void play(double *output)
{
    double curVol = myEnv.attackRelease(0.25, 1, 0.9999, 1, myEnv.trigger);
    
    currentCount = counter.phasor(1);
    myEnv.trigger = (currentCount == 1) ? 1 : 0;
    
    output[0] = curVol * myOsc.sineWave(440);
    output[1] = output[0];
}

int routing(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *userData) {
    
    unsigned int i, j;
    double *buffer = (double *) outputBuffer;
    double *lastValues = (double *) userData;
    
    if(status)
        std::cout << "Stream underflow detected!" << std::endl;
    
    for( i = 0; i<nBufferFrames; i++) {
        play(lastValues);
        for( j = 0; j < 2; j++) {
            *buffer++=lastValues[j];
        }
    }
    
    return 0;
}

//==============================================================================

int main(int argc, const char * argv[]) {
    setup();
    
    RtAudio dac(RtAudio::MACOSX_CORE);
    if(dac.getDeviceCount() < 1) {
        std::cout << "\nNo audio devices found!\n";
        exit(0);
    }
    
    RtAudio::StreamParameters parameters;
    parameters.deviceId = dac.getDefaultOutputDevice();
    parameters.nChannels = AudioSettings::channels;
    parameters.firstChannel = 0;
    unsigned int sampleRate = AudioSettings::sampleRate;
    unsigned int bufferFrames = AudioSettings::bufferSize;
    std::vector<double> data(AudioSettings::channels,0);
    
    try {
        dac.openStream( &parameters, NULL, RTAUDIO_FLOAT64,
                       sampleRate, &bufferFrames, &routing, (void *)&(data[0]));
        dac.startStream();
    } catch( RtAudioError& e) {
        std::cout << '\n' << e.getMessage() << '\n' << std::endl;
        exit( 0 );
    }
    
    char input;
    
    std::string status = dac.isStreamOpen() ? "Open" : "Closed";
    std::cout << "\nStream is open... press <enter> to quit.\n";
    std::cin.get(input);
    
    try {
        dac.stopStream();
    } catch( RtAudioError& e) {
        e.printMessage();
    }
    
    if ( dac.isStreamOpen() ) dac.closeStream();
    
    return 0;
}

//==============================================================================
