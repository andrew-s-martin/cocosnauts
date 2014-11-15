//
//  LevelScene.h
//  test
//
//  Created by Jamie Yung on 15/11/2014.
//
//

#ifndef __test__LevelScene__
#define __test__LevelScene__

#include "cocos2d.h"
#include "external/json/rapidjson.h"
#include "external/json/document.h"
#include "Entity.h"

USING_NS_CC;

class LevelScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene(const std::string &jsonStr);
    virtual bool init();
    CREATE_FUNC(LevelScene);
    
    void update(float dt);
    bool onTouchBegan(Touch *touch, Event *unused_event);
    void onTouchMoved(Touch *touch, Event *unused_event);
    void onTouchEnded(Touch *touch, Event *unused_event);
    
    bool readJson(const std::string &jsonStr);
    
private:
    Entity* buildEntity(rapidjson::Value& eSpec, const char* eType);
    void addOrbit(rapidjson::Value& oSpec, Entity* parent);
   
    Touch* curTouch;
    EventTouch::EventCode touchType;
    Entity *ship, *goal;
    std::vector<Entity*> entities;
};

#endif /* defined(__test__LevelScene__) */