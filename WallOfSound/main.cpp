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

Oscillator myOsc;

// TODO: Separate class !
void play(double *output)
{
    output[0] = myOsc.sineWave(440, 0.25);
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
    
    RtAudio dac(RtAudio::MACOSX_CORE);
    if(dac.getDeviceCount() < 1) {
        std::cout << "\nNo audio devices found!\n";
        exit(0);
    }
    
    RtAudio::StreamParameters parameters;
    parameters.deviceId = dac.getDefaultOutputDevice();
    parameters.nChannels = 2;
    parameters.firstChannel = 0;
    unsigned int sampleRate = 44100;
    unsigned int bufferFrames = 265;
    std::vector<double> data(2,0);
    
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
