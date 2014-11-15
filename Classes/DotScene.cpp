//
//  DotScene.cpp
//  test
//
//  Created by Jamie Yung on 14/11/2014.
//
//

#include "DotScene.h"

Scene* DotScene::createScene() {
    auto scene = Scene::create();
    auto layer = DotScene::create();
    scene->addChild(layer);
    return scene;
}

bool DotScene::init() {
    if (!LayerColor::init()) {
        return false;
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(DotScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(DotScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(DotScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->setColor(Color3B::WHITE);
    
    auto size = Director::getInstance()->getVisibleSize();
    int w = size.width;
    int h = size.height;
    
    for (int i = 0; i < 400; i++) {
        auto dot = new Dot(rand()%5, rand() % w, rand() % h);
        dots.push_back(dot);
    }
    
    this->scheduleUpdate();

    draw = DrawNode::create();
    this->addChild(draw);

    for (int i = 0; i < 5; i++) {
        auto e = Entity::create();
        e->setPosition(rand()%w, rand()%h);
        e->setScale(CCRANDOM_0_1() + 0.2f);
        e->mass = 1 + rand()%5;
        entities.push_back(e);
        this->addChild(e);
    }
    
    curTouch = nullptr;
    
    return true;
}

void DotScene::update(float dt) {
    updateDots(dt);
    updateEntities(dt);
    draw->clear();
    for (auto dot : dots) {
        dot->col.r = (float) (rand()%255 / 255.0);
        dot->col.g = (float) (rand()%255 / 255.0);
        dot->col.b = (float) (rand()%255 / 255.0);
        draw->drawDot(dot->pos, dot->radius, dot->col);
    }
}

void DotScene::updateEntities(float dt) {
    if (curTouch) {
        auto touchPos = curTouch->getLocation();
        for (auto e : entities) {
            auto deltaPos = touchPos - e->getPosition();
            deltaPos.normalize();
            auto maxAccel = 1 / e->mass;
            deltaPos *= maxAccel;
            e->vel.x += deltaPos.x;
            e->vel.y += deltaPos.y;
        }
    }
    for (auto e : entities) {
        e->setPosition(e->getPosition() + e->vel);
    }
}

void DotScene::updateDots(float dt) {
    if (curTouch) {
        for (auto dot : dots) {
            auto dist = Director::getInstance()->getVisibleSize().width / 4;
            auto dotDist = curTouch->getLocation().distance(dot->pos);
            float diff = 1.0 - dotDist / dist;
            float scale = 4;
            dot->radius = (dotDist < dist)? dot->original_radius * (1.0 + diff*scale) : dot->original_radius;
        }
    } else {
        for (auto dot : dots) {
            dot->radius = dot->original_radius;
        }
    }
}

bool DotScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    curTouch = touch;
    touchType = EventTouch::EventCode::BEGAN;
    return true;
}

void DotScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    curTouch = touch;
    touchType = EventTouch::EventCode::MOVED;
}

void DotScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    curTouch = nullptr;
    touchType = EventTouch::EventCode::ENDED;
}

DotScene::Dot::Dot(float radius, float x, float y) {
    this->radius = radius;
    this->original_radius = radius;
    this->pos = *new Vec2(x, y);
    this->col = *new Color4F();
    this->col.a = 1.0;
}