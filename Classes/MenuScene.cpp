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
#include "Button.h"
#include "LayoutHelper.h"
#include "FontManager.h"
#include "extensions/cocos-ext.h"
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
    
    auto fontSize = size.width/15;
    
    auto title = cocos2d::Label::createWithTTF("COCONAUTS", NSC::FontManager::getFontName(NSC::FontManager::EXTRABOLD), fontSize*2);
    title->setOpacity(0);
    title->runAction(Sequence::create(DelayTime::create(5), FadeTo::create(2, 255), NULL));
    title->setPosition(size.width/2, size.height*.8);
    title->runAction(Sequence::create(DelayTime::create(5), EaseIn::create(MoveBy::create(5, Vec2(0, -size.height*.1)), 1), NULL));
    this->addChild(title);
    
    auto start = NSC::ui::Button::create("9_sprite_rounded.png", "9_sprite_rounded.png");
    start->setPressedActionEnabled(true);
    start->setScale9Enabled(true);
    start->setTitleText("START");
    start->setTitleFontName(NSC::FontManager::getFontName(NSC::FontManager::EXTRABOLD));
    start->setTitleFontSize(fontSize);
    
    cocos2d::Label* temp = cocos2d::Label::createWithTTF("START", NSC::FontManager::getFontName(NSC::FontManager::BOLDITALIC), fontSize);
    auto lsize = temp->getContentSize();
    auto textBuffer = fontSize;
    auto capInsetSize = 32;
    
    start->setSize(Size(MAX(lsize.width + textBuffer, capInsetSize*2), MAX(lsize.height + textBuffer/2, capInsetSize*2)));
    start->setColor(Color3B(197, 217, 115));

    start->cocos2d::Node::setPosition(size.width/2, size.height*.3);
    start->addTouchEventListener([&](cocos2d::Ref* r, cocos2d::ui::Widget::TouchEventType type) {
        if (type != cocos2d::ui::Widget::TouchEventType::ENDED) {
            return;
        }
        auto scene = LevelScene::createScene(0);
        auto t = TransitionFade::create(1, scene, Color3B::BLACK);
        Director::getInstance()->pushScene(t);
    });
    start->setOpacity(0);
    start->runAction(Sequence::create(DelayTime::create(10), FadeTo::create(2, 255), NULL));
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