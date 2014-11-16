//
//  MenuScene.cpp
//  Cocosnauts
//
//  Created by Jamie Yung on 15/11/2014.
//
//

#include "MenuScene.h"
#include "BackgroundLayer.h"
#include "LevelScene.h"
#include "ButtonFactory.h"
#include "SimpleAudioEngine.h"

Scene* MenuScene::createScene() {
    auto scene = Scene::create();
    auto layer = MenuScene::create();
    scene->addChild(layer);
    return scene;
}

bool MenuScene::init() {
    if (!LayerColor::init()) {
        return false;
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(MenuScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(MenuScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(MenuScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto size = Director::getInstance()->getVisibleSize();
    
    bg = BackgroundLayer::create();
    this->addChild(bg);
    
    auto start = ButtonFactory::createButton("START");
    start->cocos2d::Node::setPosition(size.width/2, size.height/2);
    start->addTouchEventListener([&](cocos2d::Ref* r, cocos2d::ui::Widget::TouchEventType type) {
        if (type != cocos2d::ui::Widget::TouchEventType::ENDED) {
            return;
        }
        auto audio =  CocosDenshion::SimpleAudioEngine::getInstance();
        
        auto scene = LevelScene::createScene(0);
        auto t = TransitionFade::create(1, scene, Color3B::BLACK);
        Director::getInstance()->pushScene(t);
    });
    this->addChild(start);
    
    this->scheduleUpdate();
    
    return true;
}

void MenuScene::update(float dt) {
    
}

bool MenuScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    bg->onTouchBegan(touch, unused_event);
    return true;
}

void MenuScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    bg->onTouchMoved(touch, unused_event);
}

void MenuScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    bg->onTouchEnded(touch, unused_event);
}