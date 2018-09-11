//
//  main.cpp
//  WallOfSound
//
//  Created by Matthew on 11/09/2018.
//  Copyright © 2018 Matthew. All rights reserved.
//

#include <iostream>
#include "RtAudio.h"

int main(int argc, const char * argv[]) {
    std::cout << "Hello main!" << std::endl;
    
    RtAudio dac(RtAudio::MACOSX_CORE);
    if(dac.getDeviceCount() == 0) exit(0);
    
    RtAudio::StreamParameters parameters;
    parameters.deviceId = dac.getDefaultOutputDevice();
    parameters.nChannels = 2;
    unsigned int sampleRate = 44100;
    unsigned int bufferFrames = 265;
    
    RtAudio::StreamOptions options;
    options.flags = RTAUDIO_NONINTERLEAVED;
    
    try {
        dac.openStream(&parameters, NULL, RTAUDIO_FLOAT32,
                       sampleRate, &bufferFrames, nullptr, NULL, &options);
    } catch( RtAudioError& e) {
        std::cout << '\n' << e.getMessage() << '\n' << std::endl;
        exit( 0 );
    }
    
    char input;
    
    std::string status = dac.isStreamOpen() ? "Open" : "Closed";
    std::cout << "\nStream is open... press <enter> to quit.\n";
    std::cout << "Stream is: " + status << std::endl;
    std::cin.get(input);
    
    try {
        dac.stopStream();
    } catch( RtAudioError& e) {
        e.printMessage();
    }
    
    if ( dac.isStreamOpen() ) dac.closeStream();
    
    return 0;
}
