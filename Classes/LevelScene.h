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
#include "ColourManager.h"
#include "BackgroundLayer.h"
#include "Entity.h"
#include "Ship.h"
#include "FuelBar.h"
#include "MagnetPlanet.h"
#include "Button.h"
#include "BaseDialog.h"

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
    class LevelDialog : public BaseDialog {
    public:
        CREATE_FUNC(LevelDialog);
        virtual bool init();
        NSC::ui::Button*_toMenu, *_restart;
        LevelScene*scene;
        void dismiss();
    private:
        void adjustSize();
        bool onTouchBegan(Touch*touch, Event*event);
        void onTouchMoved(Touch*touch, Event*event);
        void onTouchEnded(Touch*touch, Event*event);
    };
    
    void reset();
    
    bool magnetTouched(Touch *touch);
    void handleGoalTouch(const Vec2& touchPos);
    
    void handlePauseDialogDismiss(cocos2d::Ref* r);
    
    /** If colliding with boundso or entities, reset scene */
    void checkResetCollisions();
    
    /** Update the ship's velocity */
    void updateShipVelocity(float dt);
    
    Entity* buildEntity(rapidjson::Value& eSpec, const char* eType);
    void addOrbit(rapidjson::Value& oSpec, Entity* parent);
   
    LevelDialog* dialog;
    int shipSoundId, magnetSoundId;
    EventListenerTouchOneByOne* listener;
    rapidjson::Document doc;
    BackgroundLayer* bg;
    FuelBar* fuelBar;
    int curLevel;
    Touch* curTouch;
    bool paused;
    NSC::ui::Button *level, *pauseButton;
    EventTouch::EventCode touchType;
    Entity *goal;
    Ship *ship;
    std::vector<Label*> labels;
    std::vector<Entity*> entities;
    std::vector<MagnetPlanet*> aMagnetPlanets;
};

#endif /* defined(__test__LevelScene__) */
