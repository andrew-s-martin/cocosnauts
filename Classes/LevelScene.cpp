//
//  LevelScene.cpp
//  test
//
//  Created by Jamie Yung on 15/11/2014.
//
//

#include "LevelScene.h"
#include "LevelManager.h"
#include "Ship.h"
#include "CircleEntity.h"

static const int Z_BG = -1;
static const int Z_ENTITIES = 0;
static const int Z_HUD = 1;

Scene* LevelScene::createScene(int level) {
    auto scene = Scene::create();
    auto layer = LevelScene::create();
    layer->curLevel = level;
    auto jsonStr = LevelManager::getJsonString(level);
    layer->readJson(jsonStr);
    scene->addChild(layer);
    return scene;
}

bool LevelScene::init() {
    if (!LayerColor::init()) {
        return false;
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(LevelScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(LevelScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(LevelScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->scheduleUpdate();
    
    bg = BackgroundLayer::create();
    this->addChild(bg, Z_BG);
    
    auto size = Director::getInstance()->getVisibleSize();
    fuelBar = FuelBar::create();
    fuelBar->setHeight(5);
    fuelBar->setMaxWidth(size.width);
    fuelBar->setPosition(0, size.height);
    this->addChild(fuelBar, Z_HUD);
    
    ship = Ship::create();
    ship->setColor(Color3B::RED);
    ship->setScale(0.15f);
    this->addChild(ship, Z_ENTITIES);
    
    goal = CircleEntity::create();
    goal->setColor(Color3B::GREEN);
    goal->setScale(0.15f);
    this->addChild(goal, Z_ENTITIES);
    
    curTouch = nullptr;
    
    return true;
}

void LevelScene::update(float dt) {
    for (auto e : entities) {
        e->setPosition(e->getPosition() + e->vel);
        e->updateOrbits(dt);
    }
    ship->setPosition(ship->getPosition() + ship->vel);

    if (goal->intersect(ship->getPosition(), ship->getRadius())) {
        LevelManager::goNextScene(curLevel);
    }
    for (auto e : entities) {
        if (e->intersect(ship->getPosition(), ship->getRadius())) {
        }
    }
    
    updateVelocity(dt, ship, curTouch);
}

void LevelScene::updateVelocity(float dt, Ship* ship, Touch* curTouch){
    
    Vec2 touchPos = curTouch->getLocation();
    Vec2 shipPos = ship->getPosition();
    
    //look to see if touch was inside a magnet planet
    for(auto &m : aMagnetPlanets){
        
        //if touch is within the radius of current magnet planet
        if(m->intersect(touchPos, 0.0)){
            Vec2 mPos = m->getPosition();
            ship->acc = mPos - shipPos;
            ship->acc.normalize();
            
            float lMagnetism = m->getMagnetism();
            ship->acc.scale(10*dt*lMagnetism);
            ship->vel += ship->acc;
            return;
        }
    }
    
    if (ship->getFuel() > 0 && curTouch) {
        ship->acc = touchPos - shipPos;
        ship->acc.normalize();
        ship->acc.scale(10*dt);
        ship->vel += ship->acc;
        ship->setFuel(ship->getFuel() - dt);
        fuelBar->setFillMultiplier(ship->getFuelPercent());
        CCLOG("%f", ship->getFuel());
    }
}

bool LevelScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    bg->onTouchBegan(touch, unused_event);
    curTouch = touch;
    touchType = EventTouch::EventCode::BEGAN;
    return true;
}

void LevelScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    bg->onTouchMoved(touch, unused_event);
    curTouch = touch;
    touchType = EventTouch::EventCode::MOVED;
}

void LevelScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    bg->onTouchEnded(touch, unused_event);
    curTouch = nullptr;
    touchType = EventTouch::EventCode::ENDED;
}

bool LevelScene::readJson(const std::string &jsonStr) {
    rapidjson::Document doc;
    doc.SetObject();
    
    std::string json = FileUtils::getInstance()->getStringFromFile(jsonStr);
    CCLOG("%s", json.c_str());
    doc.Parse<0>(json.c_str());
    
    for (rapidjson::Value::MemberIterator it = doc.MemberonBegin(); it != doc.MemberonEnd(); ++it) {
        rapidjson::Value&objSpec = it->value;
        const char* objType = it->name.GetString();
        
        if (strcasecmp(objType, "size") == 0) {
        }
        
        else if (strcasecmp(objType, "launchPos") == 0) {
            auto size = Director::getInstance()->getVisibleSize();
            float x = objSpec[0u].GetDouble();
            float y = objSpec[1u].GetDouble();
            ship->setPosition(x*size.width, y*size.height);
        }
        
        else if (strcasecmp(objType, "goalPos") == 0) {
            auto size = Director::getInstance()->getVisibleSize();
            float x = objSpec[0u].GetDouble();
            float y = objSpec[1u].GetDouble();
            goal->setPosition(x*size.width, y*size.height);
        }
        
        else if (strcasecmp(objType, "fuel") == 0) {
            float fuel = objSpec.GetDouble();
            CCLOG("%f", fuel);
            ship->setMaxFuel(fuel);
            ship->setFuel(fuel);
        }
        
        else if (strcasecmp(objType, "entities") == 0) {
            for (rapidjson::Value::MemberIterator it = objSpec.MemberonBegin(); it != objSpec.MemberonEnd(); ++it) {
                rapidjson::Value&eSpec = it->value;
                const char* eType = it->name.GetString();
                
                if (!eSpec.IsObject()) {
                    continue;
                }
                
                auto e = buildEntity(eSpec, eType);
                this->addChild(e, Z_ENTITIES);
                entities.push_back(e);
            }
        }
    }
    
    return true;
}

Entity* LevelScene::buildEntity(rapidjson::Value &eSpec, const char* eType) {
    Entity* e = Entity::create();
    
    // parse eType
    if (strcasecmp(eType, "planet") == 0) {
        e = CircleEntity::create();
        auto _e = static_cast<CircleEntity*>(e);
        _e->setColor(Color3B::BLUE);
    }
    else if (strcasecmp(eType, "sun") == 0) {
        e = CircleEntity::create();
        auto _e = static_cast<CircleEntity*>(e);
        _e->setColor(Color3B::YELLOW);
    }
    else if (strcasecmp(eType, "magnetPlanet") == 0) {
        auto lMagnetPlanet = MagnetPlanet::create();
        lMagnetPlanet->setMagnetism(10.0);
        aMagnetPlanets.push_back(lMagnetPlanet);
        
    }
    
    // parse properties
    for (rapidjson::Value::MemberIterator it = eSpec.MemberonBegin(); it != eSpec.MemberonEnd(); ++it) {
        rapidjson::Value&propertySpec = it->value;
        const char* propertyType = it->name.GetString();
        
        if (propertySpec.IsObject()) {
            // check if it's an orbit
            if (strcasecmp(propertyType, "orbit") == 0) {
                addOrbit(propertySpec, e);
            }
            
            // it's not an orbit, just parse it as an Entity
            else {
                auto child = buildEntity(propertySpec, propertyType);
                this->addChild(child, Z_ENTITIES);
            }
        }
        
        else if (strcasecmp(propertyType, "pos") == 0) {
            auto size = Director::getInstance()->getVisibleSize();
            float x = propertySpec[0u].GetDouble();
            float y = propertySpec[1u].GetDouble();
            e->setPosition(x*size.width, y*size.height);
        }
        else if (strcasecmp(propertyType, "mass") == 0) {
            float mass = propertySpec.GetDouble();
            e->mass = mass;
        }
        else if (strcasecmp(propertyType, "radius") == 0) {
            float radius = propertySpec.GetDouble();
            e->setScale(radius);
        }
        else if (strcasecmp(propertyType, "vel") == 0) {
            float velX = propertySpec[0u].GetDouble();
            float velY = propertySpec[1u].GetDouble();
            e->vel.set(velX, velY);
        }
    }
    
    return e;
}

void LevelScene::addOrbit(rapidjson::Value &oSpec, Entity *parent) {
    Entity::Orbit *o = new Entity::Orbit();
    for (rapidjson::Value::MemberIterator it = oSpec.MemberonBegin(); it != oSpec.MemberonEnd(); ++it) {
        rapidjson::Value&propertySpec = it->value;
        const char* propertyType = it->name.GetString();
        
        if (propertySpec.IsObject()) { // this is the actual entity that orbits parent
            o->e = buildEntity(propertySpec, propertyType);
        }
        
        else if (strcasecmp(propertyType, "radius") == 0) {
            o->radius = propertySpec.GetDouble();
        }
        
        else if (strcasecmp(propertyType, "speed") == 0) {
            o->speed = propertySpec.GetDouble();
        }
        
        else if (strcasecmp(propertyType, "angleDeg") == 0) {
            o->curAngle = propertySpec.GetDouble() * M_PI / 180;
        }
    }
    parent->addOrbit(o);
}