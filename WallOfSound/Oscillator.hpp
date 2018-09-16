//
//  Oscillator.hpp
//  WallOfSound
//
//  Created by Matthew on 15/09/2018.
//  Copyright © 2018 Matthew. All rights reserved.
//

#ifndef Oscillator_hpp
#define Oscillator_hpp

#include <stdio.h>
#include "math.h"

//==============================================================================


class Oscillator {
public:
    double phase;
    
    Oscillator();
    ~Oscillator();
    
    double sineWave(double frequency);
    double phasor(double frequency);
    
private:
    float increment;
    
    float waveTable[1024];
};
    

//==============================================================================


#endif /* Oscillator_hpp */
