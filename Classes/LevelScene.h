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
#include "BackgroundLayer.h"
#include "Entity.h"
#include "Ship.h"
#include "FuelBar.h"
#include "MagnetPlanet.h"
#include "Button.h"

USING_NS_CC;

class LevelScene : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene(int level);
    virtual bool init();
    CREATE_FUNC(LevelScene);
    
    void update(float dt);
    bool onTouchBegan(Touch *touch, Event *unused_event);
    void onTouchMoved(Touch *touch, Event *unused_event);
    void onTouchEnded(Touch *touch, Event *unused_event);
    
    bool readJson(const std::string &jsonStr);
    
private:
    void reset();
    
    /** If colliding with boundso or entities, reset scene */
    void checkResetCollisions();
    
    /** Update the ship's velocity */
    void updateShipVelocity(float dt);
    
    Entity* buildEntity(rapidjson::Value& eSpec, const char* eType);
    void addOrbit(rapidjson::Value& oSpec, Entity* parent);
   
    rapidjson::Document doc;
    BackgroundLayer* bg;
    FuelBar* fuelBar;
    NSC::ui::Button* pauseButton;
    int curLevel;
    Touch* curTouch;
    EventTouch::EventCode touchType;
    Entity *goal;
    Ship *ship;
    bool __paused;
    std::vector<Entity*> entities;
    std::vector<MagnetPlanet*> aMagnetPlanets;
};

#endif /* defined(__test__LevelScene__) */
