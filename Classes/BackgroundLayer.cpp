//
//  BackgroundLayer.cpp
//  Cocosnauts
//
//  Created by Jamie Yung on 15/11/2014.
//
//

#include "BackgroundLayer.h"

bool BackgroundLayer::init() {
    if (!LayerColor::init()) {
        return false;
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(BackgroundLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(BackgroundLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(BackgroundLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    dotCount = 400;
    minScale = 0.008f;
    scaleRange = 0.01f;
    maxTouchScaleFactor = 1.2f;
    ignoreRadius = Director::getInstance()->getVisibleSize().width / 10;
    
    generateNewDots();
    
    scheduleUpdate();
    
    return true;
}

void BackgroundLayer::generateNewDots() {
    this->removeAllChildren();
    this->dots.clear();
    
    auto size = Director::getInstance()->getVisibleSize();
    int w = size.width;
    int h = size.height;
    
    for (int i = 0; i < dotCount; i++) {
        auto dot = Dot::create();
        int x = rand() % w;
        int y = rand() % h;
        dot->setPosition(x, y);
        dot->originalScale = minScale + scaleRange * CCRANDOM_0_1();
        dot->setScale(dot->originalScale);
        dot->setColor(Color3B(CCRANDOM_0_1()*100, CCRANDOM_0_1()*100, CCRANDOM_0_1()*100));
        this->addChild(dot);
        dots.push_back(dot);
    }
}

void BackgroundLayer::setBgCol(const Color3B& col) {
    this->setColor(col);
}

void BackgroundLayer::setStarsCol(const Color3B& col) {
    for (auto dot : dots) {
        dot->setColor(col);
    }
}

void BackgroundLayer::update(float dt) {
    for (int i = 0; i < 20; i++) {
        auto dot = dots.at(rand() % dots.size());
        dot->setColor(Color3B(CCRANDOM_0_1()*100, CCRANDOM_0_1()*100, CCRANDOM_0_1()*100));
    }
}

void BackgroundLayer::updateDots(cocos2d::Touch *touch, EventTouch::EventCode type) {
    if (type == EventTouch::EventCode::ENDED ||
        type == EventTouch::EventCode::CANCELLED) {
        for (auto dot : dots) {
            dot->setScale(dot->originalScale);
        }
        return;
    }
    for (auto dot : dots) {
        auto dist = touch->getLocation().distance(dot->getPosition());
        float diff = 1.0 - dist / ignoreRadius;
        dot->setScale((dist < ignoreRadius)? dot->originalScale * (1.0 + diff*maxTouchScaleFactor) : dot->originalScale);
    }
}

bool BackgroundLayer::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    updateDots(touch, EventTouch::EventCode::BEGAN);
    return true;
}

void BackgroundLayer::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    updateDots(touch, EventTouch::EventCode::MOVED);
}

void BackgroundLayer::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    updateDots(touch, EventTouch::EventCode::ENDED);
}

bool BackgroundLayer::Dot::init() {
    if (!Sprite::initWithFile("close_normal.png")) {
        return false;
    }
    this->originalScale = 1;
    this->setPosition(0, 0);
    return true;
}