//
//  BackgroundLayer.h
//  Cocosnauts
//
//  Created by Jamie Yung on 15/11/2014.
//
//

#ifndef __Cocosnauts__BackgroundLayer__
#define __Cocosnauts__BackgroundLayer__

#include "cocos2d.h"

USING_NS_CC;

class BackgroundLayer : public cocos2d::LayerColor
{
public:
    virtual bool init();
    CREATE_FUNC(BackgroundLayer);
    
    void clear();
    void generateNewDots();
    
    void update(float dt);
    void updateDots(Touch *touch, EventTouch::EventCode type);
    
    bool onTouchBegan(Touch *touch, Event *unused_event);
    void onTouchMoved(Touch *touch, Event *unused_event);
    void onTouchEnded(Touch *touch, Event *unused_event);
    
private:
    class Dot : public cocos2d::Sprite {
    public:
        virtual bool init();
        CREATE_FUNC(Dot);
        float originalScale;
    };
    std::vector<Dot*> dots;
    
    int dotCount;
    float minScale, scaleRange;
    float maxTouchScaleFactor;
    float ignoreRadius;
};

#endif /* defined(__Cocosnauts__BackgroundLayer__) */
