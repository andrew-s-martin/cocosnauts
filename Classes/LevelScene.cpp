//
//  LevelScene.cpp
//  test
//
//  Created by Jamie Yung on 15/11/2014.
//
//

#include "LevelScene.h"

Scene* LevelScene::createScene(const std::string &jsonStr) {
    auto scene = Scene::create();
    auto layer = LevelScene::create();
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
    
    ship = Entity::create();
    this->addChild(ship);
    
    goal = Entity::create();
    this->addChild(goal);
    
    curTouch = nullptr;
    
    return true;
}

void LevelScene::update(float dt) {
    for (auto e : entities) {
        e->setPosition(e->getPosition() + e->vel);
        for (auto o : e->orbits) {
            o->curAngle += o->speed * 2 * M_PI * dt;
            auto parentRadius = e->sprite->getContentSize().height/2;
            float x = cosf(o->curAngle) * o->radius * parentRadius;
            float y = sinf(o->curAngle) * o->radius * parentRadius;
            o->e->setPosition(x, y);
        }
    }
}

bool LevelScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    curTouch = touch;
    touchType = EventTouch::EventCode::BEGAN;
    return true;
}

void LevelScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    curTouch = touch;
    touchType = EventTouch::EventCode::MOVED;
}

void LevelScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
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
        
        else if (strcasecmp(objType, "entities") == 0) {
            for (rapidjson::Value::MemberIterator it = objSpec.MemberonBegin(); it != objSpec.MemberonEnd(); ++it) {
                rapidjson::Value&eSpec = it->value;
                const char* eType = it->name.GetString();
                
                if (!eSpec.IsObject()) {
                    continue;
                }
                
                auto e = buildEntity(eSpec, eType);
                this->addChild(e);
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
        e->sprite->setColor(Color3B::BLUE);
    }
    else if (strcasecmp(eType, "sun") == 0) {
        e->sprite->setColor(Color3B::YELLOW);
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
                this->addChild(child);
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
        
        else if (strcasecmp(propertyType, "clockwise") == 0) {
            o->clockwise = propertySpec.GetBool();
        }
    }
    auto parentRadius = parent->sprite->getContentSize().height/2;
    o->e->setPositionX(o->radius*parentRadius);
    parent->addChild(o->e);
    parent->orbits.push_back(o);
}