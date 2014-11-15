//
//  NextScene.h
//  test
//
//  Created by Jamie Yung on 14/11/2014.
//
//

#ifndef __test__NextScene__
#define __test__NextScene__

#include "cocos2d.h"

USING_NS_CC;

class NextScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(NextScene);
    void update(float delta);
    
    bool onTouchBegan(Touch *touch, Event *unused_event);
    void onTouchMoved(Touch *touch, Event *unused_event);
    void onTouchEnded(Touch *touch, Event *unused_event);
    
private:
    Label *label;
};

#endif /* defined(__test__NextScene__) */
