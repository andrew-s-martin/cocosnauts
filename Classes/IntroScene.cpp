//
//  IntroScene.cpp
//  Cocosnauts
//
//  Created by Jamie Yung on 16/11/2014.
//
//

#include "IntroScene.h"
#include "MenuScene.h"
#include "FontManager.h"
#include "SimpleAudioEngine.h"

Scene* IntroScene::createScene() {
    auto scene = Scene::create();
    auto layer = IntroScene::create();
    scene->addChild(layer);
    return scene;
}

bool IntroScene::init() {
    if (!LayerColor::initWithColor(Color4B::WHITE)) {
        return false;
    }
    
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(IntroScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(IntroScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(IntroScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto audio =  CocosDenshion::SimpleAudioEngine::getInstance();
    audio->preloadBackgroundMusic("inonzur.mp3");
    audio->playBackgroundMusic("inonzur.mp3", true);
    audio->preloadEffect("zap.wav");
    audio->preloadEffect("bloop.mp3");
    audio->preloadEffect("ship.mp3");
    audio->preloadEffect("goal.mp3");
    audio->preloadEffect("whoosh.mp3");
    
    auto size = Director::getInstance()->getVisibleSize();
    
    layer = Layer::create();
    layer->setCascadeOpacityEnabled(true);
    layer->setContentSize(Size::ZERO);
    layer->setPosition(size.width/2, size.height/2);
    this->addChild(layer);
    
    auto left = Sprite::create("close_normal.png");
    left->setColor(Color3B::BLACK);
    left->setScale(0.1f);
    left->setPositionX(-size.width*0.3);
    layer->addChild(left);
    
    auto right = Sprite::create("close_normal.png");
    right->setColor(Color3B::BLACK);
    right->setScale(0.1f);
    right->setPositionX(size.width*0.3);
    layer->addChild(right);
    
    auto label = Label::createWithTTF("Team Cocosnuts",
                                  NSC::FontManager::getFontName(NSC::FontManager::EXTRABOLDITALIC),
                                  size.width / 25);
    label->setAlignment(TextHAlignment::CENTER);
    label->setAnchorPoint(Vec2(0.5, 0.5));
    label->setPosition(size.width/2, size.height/2);
    label->setColor(Color3B::BLACK);
    
    layer->setOpacity(0);
    layer->runAction(Sequence::create(DelayTime::create(2.0), FadeTo::create(10.0, 255), NULL));
    
    label->setOpacity(0);
    label->runAction(Sequence::create(DelayTime::create(2.0), FadeTo::create(10.0, 255), NULL));
    
    label->runAction(ScaleTo::create(10.0, 1.4));
    this->addChild(label);
    
    this->scheduleUpdate();
    this->scheduleOnce(schedule_selector(IntroScene::goNext), 12);
    
    return true;
}

void IntroScene::update(float dt) {
    layer->setRotation(layer->getRotation() + 1);
}

void IntroScene::goNext(float dt) {
    auto scene = MenuScene::createScene();
    auto t = TransitionFade::create(4, scene, Color3B::BLACK);
    Director::getInstance()->replaceScene(t);
}

bool IntroScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    return true;
}

void IntroScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event) {
    goNext(0);
}