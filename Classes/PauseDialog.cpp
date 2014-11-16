//
//  PauseDialog.cpp
//  ChessExplorer
//
//  Created by Jamie Yung on 24/07/2014.
//
//

#include "PauseDialog.h"
#include "ButtonFactory.h"

bool PauseDialog::init() {
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
    
    this->adjustSize();
    
    return true;
}

void PauseDialog::adjustSize() {
    BaseDialog::adjustSize();
    
    auto contentBB = getContentBoundingBox();
    _toMenu->cocos2d::Node::setPosition(contentBB.getMidX(), contentBB.getMidY());
}

bool PauseDialog::onTouchBegan(Touch*touch, cocos2d::Event *event) {
    if (!BaseDialog::onTouchBegan(touch, event)) {
        return true; // swallow the touch
    }
    auto touchPt = touch->getLocation();
    
    return true;
}

void PauseDialog::onTouchMoved(Touch*touch, cocos2d::Event *event) {
}

void PauseDialog::onTouchEnded(Touch*touch, cocos2d::Event *event) {
}