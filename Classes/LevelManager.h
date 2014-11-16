//
//  LevelManager.h
//  Cocosnauts
//
//  Created by Jamie Yung on 15/11/2014.
//
//

#ifndef __Cocosnauts__LevelManager__
#define __Cocosnauts__LevelManager__

#include "cocos2d.h"

USING_NS_CC;

class LevelManager {
public:
    static const std::string getJsonString(int level);
    static void goNextScene(int curLevel);
};

#endif /* defined(__Cocosnauts__LevelManager__) */
