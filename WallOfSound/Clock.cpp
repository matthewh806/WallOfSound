//
//  Clock.cpp
//  WallOfSound
//
//  Created by Matthew on 16/09/2018.
//  Copyright © 2018 Matthew. All rights reserved.
//

#include "Clock.hpp"
#include <iostream>

Clock::Clock()
{
    playHead = 0;
    currentCount = 0;
    lastCount = 0;
    bpm = 120;
    ticks = 1;
    
    setTempo(bpm);
}

void Clock::ticker()
{
    tick = false;
    currentCount = floor(timer.phasor(bps)); // metronome
    
    // currentCount is always 0 or 1, lastCount is always 0
    if(lastCount != currentCount) {
        tick = true;
        playHead++;
    }
}

void Clock::setTempo(double bpmIn)
{
    bpm = bpmIn;
    bps = (bpm / 60.) * ticks;
}

void Clock::setTicksPerBeat(int ticksPerBeat)
{
    ticks = ticksPerBeat;
    setTempo(bpm);
}
