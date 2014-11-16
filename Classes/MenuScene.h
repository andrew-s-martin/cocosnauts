//
//  MenuScene.h
//  Cocosnauts
//
//  Created by Jamie Yung on 15/11/2014.
//
//

#ifndef __Cocosnauts__MenuScene__
#define __Cocosnauts__MenuScene__

#include "cocos2d.h"
#include "BackgroundLayer.h"

USING_NS_CC;

class MenuScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MenuScene);
    
    void update(float dt);
    bool onTouchBegan(Touch *touch, Event *unused_event);
    void onTouchMoved(Touch *touch, Event *unused_event);
    void onTouchEnded(Touch *touch, Event *unused_event);
    
private:
    BackgroundLayer* bg;
};

#endif /* defined(__Cocosnauts__MenuScene__) */
