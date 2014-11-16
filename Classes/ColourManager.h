//
//  ColourManager.h
//  Cocosnauts
//
//  Created by Jamie Yung on 16/11/2014.
//
//

#ifndef __Cocosnauts__ColourManager__
#define __Cocosnauts__ColourManager__

#include "cocos2d.h"
#include "external/json/rapidjson.h"
#include "external/json/document.h"

USING_NS_CC;

class ColourManager {
public:
    static const Color3B bgCol;
    static const Color3B bgStars;
    static const Color3B planet;
    static const Color3B sun;
    static const Color3B ship;
    static const Color3B goal;
    static const Color3B magnetPlanet;
};

#endif /* defined(__Cocosnauts__ColourManager__) */
