//
//  Envelope.cpp
//  WallOfSound
//
//  Created by Matthew on 15/09/2018.
//  Copyright © 2018 Matthew. All rights reserved.
//

#include "Envelope.hpp"

//==============================================================================
Envelope::Envelope()
{
}

Envelope::~Envelope()
{
}

//==============================================================================

double Envelope::attackRelease(double input, double attack, double release, long holdTime, int trigger)
{
    if(trigger == 1 && attackPhase != 1 && holdPhase != 1)
    {
        holdCount = 0;
        releasePhase = 0;
        attackPhase = 1;
    }
    
    if(attackPhase == 1)
    {
        amplitude += attack;
        output = input * amplitude;
        
    }
    
    if(amplitude >= 1) {
        amplitude = 1;
        attackPhase = 0;
        holdPhase = 1;
    }
    
    if(holdCount < holdTime && holdPhase == 1)
    {
        output = input;
        holdCount++;
    }
    
    if(holdCount == holdTime && trigger == 1)
    {
        output = input;
    }
    
    if(holdCount == holdTime && trigger != 1)
    {
        holdPhase = 0;
        releasePhase = 1;
    }
    
    if(releasePhase == 1 && amplitude > 0.0)
    {
        output = input * (amplitude *= release);
    }
    
    return output;
}
