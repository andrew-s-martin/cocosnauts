//
//  DotScene.h
//  test
//
//  Created by Jamie Yung on 14/11/2014.
//
//

#ifndef __test__DotScene__
#define __test__DotScene__

#include "cocos2d.h"
#include "Entity.h"

USING_NS_CC;

class DotScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(DotScene);
    void update(float dt);
    
    bool onTouchBegan(Touch *touch, Event *unused_event);
    void onTouchMoved(Touch *touch, Event *unused_event);
    void onTouchEnded(Touch *touch, Event *unused_event);
    
private:
    void updateEntities(float dt);
    void updateDots(float dt);
    
    class Dot {
    public:
        Dot(float radius, float x, float y);
        Vec2 pos;
        float radius, original_radius;
        Color4F col;
    };
    std::vector<Dot*> dots;
    DrawNode* draw;
    std::vector<Entity*> entities;
    Touch* curTouch;
    EventTouch::EventCode touchType;
};

#endif /* defined(__test__DotScene__) */
