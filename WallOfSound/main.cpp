//
//  main.cpp
//  WallOfSound
//
//  Created by Matthew on 11/09/2018.
//  Copyright © 2018 Matthew. All rights reserved.
//

#include <iostream>
#include "math.h"
#include <vector>
#include "RtAudio.h"

//==============================================================================

class audioSettings {
    
public:
    static int sampleRate;
    static int channels;
    static int bufferSize;
};

//==============================================================================

// TODO: Separate class!

template< int TABLE_SIZE >

class osc {
public:
    double frequency;
    double phase;
    
    osc() {
        phase = 0.0;
        bufferSize = TABLE_SIZE;
        
        auto angleDelta = M_PI_2 / (bufferSize - 1);
        auto currentAngle = 0.0;
        
        for(int i = 0; i < bufferSize; i++) {
            sineBuffer[i] = sin(currentAngle);
            currentAngle += angleDelta;
        }
    }
    
    double sineWave(double frequency)
    {
        // phase index = mod_L ( previous_phase + increment) L = length
        // output = amplitude * wavetable[phase_index]
        
        auto output = 0.25 * sineBuffer[(int)phase];
        
        increment = (bufferSize * frequency) / 44100;
        phase = fmod(phase + increment, bufferSize);
        
        return output;
    }
    
private:
    int bufferSize;
    float increment;
    
    float sineBuffer[TABLE_SIZE];
};


//==============================================================================

osc<1024> myOsc;

// TODO: Separate class !
void play(double *output)
{
    
    // TODO: Play!
    output[0] = myOsc.sineWave(440);
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
    
//    audioSettings::sampleRate = 44100;
//    audioSettings::channels = 2;
//    audioSettings::bufferSize = 1024;
    
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
