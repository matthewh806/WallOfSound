//
//  AudioSettings.hpp
//  WallOfSound
//
//  Created by Matthew on 15/09/2018.
//  Copyright © 2018 Matthew. All rights reserved.
//

#ifndef AudioSettings_hpp
#define AudioSettings_hpp

#include <stdio.h>

//==============================================================================

class AudioSettings {
    
public:
    static int sampleRate;
    static int channels;
    static int bufferSize;
};

//==============================================================================

#endif /* AudioSettings_hpp */
