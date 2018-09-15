//
//  Envelope.hpp
//  WallOfSound
//
//  Created by Matthew on 15/09/2018.
//  Copyright © 2018 Matthew. All rights reserved.
//

#ifndef Envelope_hpp
#define Envelope_hpp

#include <stdio.h>

//==============================================================================

class Envelope {
    
public:
    Envelope();
    ~Envelope();
    
    double attackRelease(double input, double attack = 1, double release = 0.9, long holdTime=1, int trigger=0);
    
    double input;
    double output;
    double attack;
    double decay;
    double sustain;
    double release;
    double amplitude;
    
    int trigger;
    long holdTime = 1;
    long holdCount ;
    
    int attackPhase, decayPhase, sustainPhase, holdPhase, releasePhase;
};


//==============================================================================


#endif /* Envelope_hpp */
