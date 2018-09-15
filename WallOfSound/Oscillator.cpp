//
//  Oscillator.cpp
//  WallOfSound
//
//  Created by Matthew on 15/09/2018.
//  Copyright © 2018 Matthew. All rights reserved.
//

#include "Oscillator.hpp"
#include "AudioSettings.hpp"

//==============================================================================

Oscillator::Oscillator()
{
    phase = 0.0;
    
    auto angleDelta = M_PI_2 / (AudioSettings::bufferSize - 1);
    auto currentAngle = 0.0;
    
    for(int i = 0; i < AudioSettings::bufferSize; i++) {
        waveTable[i] = sin(currentAngle);
        currentAngle += angleDelta;
    }
}

Oscillator::~Oscillator()
{
    // TODO: Cleanup
}

double Oscillator::sineWave(double frequency, double amplitude)
{
    // phase index = mod_L ( previous_phase + increment) L = length
    // output = amplitude * wavetable[phase_index]
    
    // Lerp between values to get output: (1-t) * v0 + t * v1;
    int index0 = (int)phase;
    int index1 = (index0 == AudioSettings::bufferSize - 1) ? 0 : index0 + 1;
    
    auto value0 = waveTable[index0];
    auto value1 = waveTable[index1];
    auto t = phase - (float)index0;
    
    auto output = amplitude * (1-t) * value0 + t * value1;
    
    increment = (AudioSettings::bufferSize * frequency) / AudioSettings::sampleRate;
    phase = fmod(phase + increment, AudioSettings::bufferSize);
    
    return output;
}

//==============================================================================
