//
//  main.cpp
//  WallOfSound
//
//  Created by Matthew on 11/09/2018.
//  Copyright © 2018 Matthew. All rights reserved.
//

#include <iostream>
#include "RtAudio.h"

int saw(void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
         double streamTime, RtAudioStreamStatus status, void *userData) {
    
    unsigned int i, j;
    double *buffer = (double *) outputBuffer;
    double *lastValues = (double *) userData;
    
    if(status)
        std::cout << "Stream underflow detected!" << std::endl;
    
    for( i = 0; i<nBufferFrames; i++) {
        for( j = 0; j < 2; j++) {
            *buffer++ = lastValues[j];
            
            lastValues[j] += 0.005 * (j+1+(j*0.1));
            if(lastValues[j] >= 1.0) lastValues[j] -= 2.0;
        }
    }
    
    return 0;
}

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
    double data[2];
    
    try {
        dac.openStream(&parameters, NULL, RTAUDIO_FLOAT32,
                       sampleRate, &bufferFrames, &saw, (void *)&data);
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
