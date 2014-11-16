//
//  MagnetPlanet.h
//  Test
//
//  Created by Charles Bloomfield on 11/16/14.
//
//

#ifndef __Test__MagnetPlanet__
#define __Test__MagnetPlanet__

#include <stdio.h>
#include "CircleEntity.h"

class MagnetPlanet: public CircleEntity {
public:
    virtual bool init();
    CREATE_FUNC(MagnetPlanet);
    
    float getMagnetism();
private:
    float aMagnetism;
};

#endif /* defined(__Test__MagnetPlanet__) */
