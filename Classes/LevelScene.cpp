//
//  LevelScene.cpp
//  test
//
//  Created by Jamie Yung on 15/11/2014.
//
//

#include "ButtonFactory.h"
#include "LevelScene.h"
#include "LevelManager.h"
#include "Ship.h"
#include "CircleEntity.h"
#include "FontManager.h"
#include "LayoutHelper.h"
#include "BackgroundLayer.h"
#include "SimpleAudioEngine.h"

static const int Z_BG = -1;
static const int Z_ENTITIES = 0;
static const int Z_GOAL = 1;
static const int Z_SHIP = 2;
static const int Z_FUELBAR = 3;
static const int Z_HUD = 4;
static const int Z_DIALOG = 5;

Scene* LevelScene::createScene(int level) {
    auto scene = Scene::create();
    auto layer = LevelScene::create();
    layer->curLevel = level;
    layer->reset();
    scene->addChild(layer);
    return scene;
}

bool LevelScene::init() {
    if (!LayerColor::init()) {
        return false;
    }
    
    listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(LevelScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(LevelScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(LevelScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    doc.SetObject();
    
    bg = BackgroundLayer::create();
    this->addChild(bg, Z_BG);
    
    auto size = Director::getInstance()->getVisibleSize();
    
    fuelBar = FuelBar::create();
    this->addChild(fuelBar, Z_FUELBAR);
    
    std::stringstream ss;
    ss << curLevel;
    auto string = "LEVEL " + ss.str();
    level = ButtonFactory::createButton(string.c_str());
    level->Button::setColor(Color3B::WHITE);
    level->Button::loadTextures("9_sprite_square.png", "9_sprite_square.png");
    level->setTouchEnabled(false);
    auto levelSize = level->getContentSize();
    level->cocos2d::Node::setPosition(levelSize.width/2, size.height - levelSize.height/2);
    this->addChild(level, Z_HUD);
    
    pauseButton = ButtonFactory::createButton("||");
    auto pauseSize = pauseButton->getContentSize();
    pauseButton->cocos2d::Node::setPosition(size.width - pauseSize.width/2, size.height - pauseSize.height/2);
    pauseButton->addTouchEventListener([&](cocos2d::Ref* r, cocos2d::ui::Widget::TouchEventType type) {
        if (type == ui::Widget::TouchEventType::ENDED) {
            paused = !paused;
            pauseButton->setTitleText(paused? "O" : "||");
            if (paused) {
                this->unscheduleUpdate();
                auto l = LayerColor::create(Color4B(0, 0, 0, 0));
                this->addChild(l, Z_DIALOG);
                l->runAction(FadeTo::create(0.1f, 150));
                l->setTag(420); // blaze it
                dialog = LevelDialog::create();
                dialog->scene = this;
                dialog->_restart->addTouchEventListener([&](cocos2d::Ref* r, cocos2d::ui::Widget::TouchEventType type) {
                    if (type == ui::Widget::TouchEventType::ENDED) {
                        this->reset();
                        dialog->dismiss();
                    }
                });
                this->addChild(dialog, Z_DIALOG);
                dialog->show();
            } else {
                this->scheduleUpdate();
            }
        }
    });
    pauseButton->Button::setColor(Color3B::WHITE);
    pauseButton->Button::loadTextures("9_sprite_square.png", "9_sprite_square.png");
    this->addChild(pauseButton, Z_HUD);

    fuelBar->setHeight(pauseSize.height);
    
    goal = CircleEntity::create();
    this->addChild(goal, Z_GOAL);
    
    ship = Ship::create();
    this->addChild(ship, Z_SHIP);
    
    this->reset();
    
    this->scheduleUpdate();
    
    return true;
}

void LevelScene::reset() {
    auto size = Director::getInstance()->getVisibleSize();
    
    std::stringstream ss;
    ss << curLevel;
    auto string = "LEVEL " + ss.str();
    level->setTitleText(string);
    
    bg->setBgCol(ColourManager::bgCol);
    
    fuelBar->setMaxWidth(size.width - level->getContentSize().width - pauseButton->getContentSize().width);
    fuelBar->setPosition(level->getContentSize().width, size.height);
    
    this->removeChild(ship);
    ship = Ship::create();
    ship->setColor(ColourManager::ship);
    ship->setScale(0.15f);
    this->addChild(ship);
    
    goal->setColor(ColourManager::goal);
    goal->setScale(0.15f);
    
    curTouch = nullptr;
    touchType = EventTouch::EventCode::ENDED;
    
    for (auto l : labels) {
        this->removeChild(l);
    }
    
    for (auto e : entities) {
        this->removeChild(e);
    }
    
    labels.clear();
    entities.clear();
    aMagnetPlanets.clear();
    
    auto jsonStr = LevelManager::getJsonString(curLevel);
    readJson(jsonStr);
}

void LevelScene::handleGoalTouch(const cocos2d::Vec2 &touchPos) {
    paused = true;
    this->_eventDispatcher->removeEventListener(listener);
    this->unscheduleUpdate();
    auto circle = Sprite::create("close_normal.png");
    this->addChild(circle, Z_DIALOG);
    circle->setPosition(touchPos);
    circle->setScale(0);
    circle->runAction(EaseOut::create(ScaleTo::create(0.2, 10), 2.0f));
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->playEffect("goal.mp3");
    audio->playEffect("whoosh.mp3");
    audio->stopEffect(shipSoundId);
    audio->stopEffect(magnetSoundId);
    LevelManager::goNextLevel(curLevel);
}

void LevelScene::handlePauseDialogDismiss(cocos2d::Ref* r) {
    this->scheduleUpdate();
    paused = false;
    pauseButton->setTitleText("||");
    auto l = this->getChildByTag(420); // smoke weed every day
    l->runAction(FadeTo::create(0.1f, 0));
    l->runAction(Sequence::create(DelayTime::create(0.2f),
                                     RemoveSelf::create(), NULL));
}

void LevelScene::update(float dt) {
    for (auto e : entities) {
        e->setPosition(e->getPosition() + e->vel);
        e->updateOrbits(dt);
    }
    ship->setPosition(ship->getPosition() + ship->vel);

    if (goal->intersect(ship->getPosition(), ship->getRadius())) {
        handleGoalTouch(ship->getPosition());
    }
    
    checkResetCollisions();
    updateShipVelocity(dt);
    
    float lAngleInDegrees = atan2f(ship->vel.x, ship->vel.y) * (180 / M_PI);
    ship->setRotation(lAngleInDegrees);
}

void LevelScene::checkResetCollisions() {
    auto b = this->getBoundingBox();
    
    if (!b.containsPoint(ship->getPosition())) {
        reset();
        return;
    }
    
    for (auto e : entities) {
        if (e->intersect(ship->getPosition(), ship->getRadius())) {
            reset();
            return;
        }
    }
}

void LevelScene::updateShipVelocity(float dt) {
    if (!curTouch) {
        return;
    }
    
    Vec2 shipPos = ship->getPosition();
    Vec2 touchPos = curTouch->getLocation();
    
    //look to see if touch was inside a magnet planet
    for(auto &m : aMagnetPlanets) {
        //if touch is within the radius of current magnet planet
        if(m->intersect(touchPos, 0.0)) {
            m->setColor(Color3B(0,255,0));
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
    } else {
        auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
        audio->stopEffect(shipSoundId);
    }
}

bool LevelScene::magnetTouched(cocos2d::Touch *touch) {
    for(auto &m : aMagnetPlanets) {
        if(m->intersect(touch->getLocation(), 0.0)) {
            return true;
        }
    }
    return false;
}

bool LevelScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    bg->onTouchBegan(touch, unused_event);
    curTouch = touch;
    touchType = EventTouch::EventCode::BEGAN;
    
    auto audio =  CocosDenshion::SimpleAudioEngine::getInstance();
    shipSoundId = audio->playEffect("ship.mp3", true);
    if (magnetTouched(touch)) {
        magnetSoundId = audio->playEffect("zap.wav", true);
    }
    
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
    for(auto &m : aMagnetPlanets) {
        m->setColor(ColourManager::magnetPlanet);
    }
    
    auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
    audio->stopEffect(shipSoundId);
    audio->stopEffect(magnetSoundId);
}

bool LevelScene::readJson(const std::string &jsonStr) {
    std::string json = FileUtils::getInstance()->getStringFromFile(jsonStr);
    doc.Parse<0>(json.c_str());
    
    for (rapidjson::Value::MemberIterator it = doc.MemberonBegin(); it != doc.MemberonEnd(); ++it) {
        rapidjson::Value&objSpec = it->value;
        const char* objType = it->name.GetString();
        
        if (strcasecmp(objType, "levelSize") == 0) {
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
            ship->setMaxFuel(fuel);
            ship->setFuel(fuel);
        }
        
        else if (strcasecmp(objType, "labels") == 0) {
            auto size = Director::getInstance()->getVisibleSize();
            for (rapidjson::Value::MemberIterator it = objSpec.MemberonBegin(); it != objSpec.MemberonEnd(); ++it) {
                rapidjson::Value&eSpec = it->value;
                const char* text = it->name.GetString();
                auto x = eSpec[0u].GetDouble();
                auto y = eSpec[1u].GetDouble();
                auto l = Label::createWithTTF(text, NSC::FontManager::getFontName(NSC::FontManager::LIGHTITALIC), LayoutHelper::getNormalFontSize());
                l->setPosition(x * size.width, y * size.height);
                labels.push_back(l);
                this->addChild(l);
            }
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
        _e->setColor(ColourManager::planet);
    }
    else if (strcasecmp(eType, "sun") == 0) {
        e = CircleEntity::create();
        auto _e = static_cast<CircleEntity*>(e);
        _e->setColor(ColourManager::sun);
    }
    else if (strcasecmp(eType, "magnetPlanet") == 0) {
        e = MagnetPlanet::create();
        auto _e = static_cast<MagnetPlanet*>(e);
        _e->setColor(ColourManager::magnetPlanet);
        aMagnetPlanets.push_back(_e);
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
        else if (strcasecmp(propertyType, "magnetism") == 0) {
            auto _e = static_cast<MagnetPlanet*>(e);
            if (_e) {
                float magnetism = propertySpec.GetDouble();
                _e->setMagnetism(magnetism);
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

bool LevelScene::LevelDialog::init() {
    if (!BaseDialog::init()) {
        return false;
    }
    
    this->_title->setString("PAUSE");
    
    _toMenu = ButtonFactory::createButton("MENU");
    _toMenu->addTouchEventListener([&](Ref* r, cocos2d::ui::Widget::TouchEventType type){
        if (type != cocos2d::ui::Widget::TouchEventType::ENDED) {
            return;
        }
        Director::getInstance()->popToRootScene();
        this->dismiss();
    });
    box->addChild(_toMenu);
    
    _restart = ButtonFactory::createButton("RESTART LEVEL");
    box->addChild(_restart);
    
    this->adjustSize();
    
    return true;
}

void LevelScene::LevelDialog::dismiss() {
    this->scene->handlePauseDialogDismiss(this);
    BaseDialog::dismiss();
}

void LevelScene::LevelDialog::adjustSize() {
    BaseDialog::adjustSize();
    
    auto contentBB = getContentBoundingBox();
    auto size = contentBB.size;
    _toMenu->cocos2d::Node::setPosition(contentBB.getMidX(), size.height*.7);
    _restart->cocos2d::Node::setPosition(contentBB.getMidX(), size.height*.3);
}

bool LevelScene::LevelDialog::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event) {
    if (!BaseDialog::onTouchBegan(touch, event)) {
        return true; // swallow the touch
    }
    auto touchPt = touch->getLocation();
    
    return true;
}

void LevelScene::LevelDialog::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event) {
    
}

void LevelScene::LevelDialog::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event) {
    
}