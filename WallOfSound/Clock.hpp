//
//  Clock.hpp
//  WallOfSound
//
//  Created by Matthew on 16/09/2018.
//  Copyright © 2018 Matthew. All rights reserved.
//

#ifndef Clock_hpp
#define Clock_hpp

#include <stdio.h>
#include "Oscillator.hpp"

//==============================================================================

class Clock {
public:
    Clock();
    
    void ticker();
    void setTempo(double bpm);
    void setTicksPerBeat(int ticksPerBeat);
    
    Oscillator timer;
    int currentCount;
    int lastCount;
    int playHead;
    double bps;
    double bpm;
    int ticks;
    bool tick;
};

//==============================================================================


#endif /* Clock_hpp */
