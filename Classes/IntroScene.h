//
//  IntroScene.h
//  Cocosnauts
//
//  Created by Jamie Yung on 16/11/2014.
//
//

#ifndef __Cocosnauts__IntroScene__
#define __Cocosnauts__IntroScene__

#include "cocos2d.h"

USING_NS_CC;

class IntroScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(IntroScene);
    
    void update(float dt);
    bool onTouchBegan(Touch *touch, Event *unused_event);
    void onTouchEnded(Touch *touch, Event *unused_event);
private:
    void goNext(float dt);
    Layer*layer;
};

#endif /* defined(__Cocosnauts__IntroScene__) */
