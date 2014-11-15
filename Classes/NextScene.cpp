//
//  NextScene.cpp
//  test
//
//  Created by Jamie Yung on 14/11/2014.
//
//

#include "NextScene.h"

USING_NS_CC;

Scene* NextScene::createScene()
{
    auto scene = Scene::create();
    auto layer = NextScene::create();
    scene->addChild(layer);
    return scene;
}

bool NextScene::init() {
    if (!Layer::init()) {
        return false;
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(NextScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(NextScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(NextScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    label = Label::createWithSystemFont("Next scene bitch3zzzz", "Arial", 72);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    label->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    this->addChild(label, 1);
    
    this->scheduleUpdate();
    
    return true;
}

void NextScene::update(float delta)
{
    label->setColor(Color3B(rand()%255, rand()%255, rand()%255));
    label->setRotation(label->getRotation() + 10);
}

bool NextScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    label->setPosition(touch->getLocation());
    return true;
}

void NextScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    label->setPosition(touch->getLocation());
}

void NextScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    label->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
}