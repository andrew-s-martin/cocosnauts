//
//  BaseDialog.cpp
//  ChessExplorer
//
//  Created by Jamie Yung on 21/07/2014.
//
//

#include "BaseDialog.h"
#include "FontManager.h"
#include "LayoutHelper.h"
#include "ButtonFactory.h"

bool BaseDialog::init() {
    if (!Layer::init()) {
        return false;
    }
    
    this->ignoreAnchorPointForPosition(false);
    this->setAnchorPoint(Vec2(0.5, 0.5));
    
    _dismissNotificationString = "BaseDialogDismiss-Default";
    _animateShowDismiss = true;
    setCascadeOpacityEnabled(true);
    
    listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(BaseDialog::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(BaseDialog::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(BaseDialog::onTouchEnded, this);
    listener->setSwallowTouches(true);
    
    edgeMargin = LayoutHelper::getDialogEdgeMargin();
    innerMargin = LayoutHelper::getDialogInnerMargin();
    
    auto batchNode_box = SpriteBatchNode::create("9_sprite_rounded.png");
    box = extension::Scale9Sprite::create();
    box->updateWithBatchNode(batchNode_box, Rect(0, 0, 96, 96), false, Rect(32, 32, 32, 32));
    this->addChild(box, 0);
    
    _title = Label::createWithTTF("BaseDialog", NSC::FontManager::getFontName(NSC::FontManager::BOLDITALIC), LayoutHelper::getNormalFontSize());
    _title->setColor(Color3B(0, 0, 0));
    box->addChild(_title);
    
    _closeButton = ButtonFactory::createButton("X");
    _closeButton->setColor(Color3B::RED);
    _closeButton->addTouchEventListener([&](Ref* r, cocos2d::ui::Widget::TouchEventType type){
        if (type != cocos2d::ui::Widget::TouchEventType::ENDED) {
            return;
        }
        this->dismiss();
    });
    this->addChild(_closeButton);
    
    return true;
}

void BaseDialog::setDismissNotificationString(std::string str) {
    _dismissNotificationString = str;
}

void BaseDialog::setAnimateShowDismiss(bool animate) {
    _animateShowDismiss = animate;
}

void BaseDialog::show() {
    this->setVisible(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    if (_animateShowDismiss) {
        this->setScale(0.9);
        this->runAction(EaseElasticOut::create(ScaleTo::create(0.6, 1)));
    }
}

void BaseDialog::dismiss() {
    NotificationCenter::getInstance()->postNotification(_dismissNotificationString, this);
    _eventDispatcher->removeEventListener(listener);
    if (_animateShowDismiss) {
        this->runAction(EaseBackIn::create(ScaleBy::create(0.2, 0)));
        this->runAction(Sequence::create(DelayTime::create(0.5),
                                         RemoveSelf::create(), NULL));
    } else {
        this->removeFromParent();
    }
}

/** In the co-ord system of the box, ie. relative to the bottom left corner of the box sprite. */
Rect BaseDialog::getContentBoundingBox() const {
    auto boxSize = box->getContentSize();
    Rect rect = Rect(innerMargin, innerMargin, boxSize.width-innerMargin*2, boxSize.height-innerMargin*2-titleBarHeight);
    return rect;
}

void BaseDialog::adjustSize() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto boxSize = Size(visibleSize.width - edgeMargin*2, visibleSize.height - edgeMargin*2);
    this->setContentSize(boxSize);
    box->setContentSize(boxSize);
    this->setPosition(visibleSize.width/2, visibleSize.height/2);
    box->setPosition(boxSize.width/2, boxSize.height/2);
    
    titleBarHeight = innerMargin*3;
    _title->setPosition(boxSize.width/2, boxSize.height - titleBarHeight/2);
    
    _closeButton->cocos2d::Node::setPosition(boxSize.width - innerMargin,
                                             boxSize.height - innerMargin);
}

bool BaseDialog::onTouchBegan(Touch*touch, cocos2d::Event *event) {
    auto touchPt = touch->getLocation();
    if (!box->getBoundingBox().containsPoint(touchPt)) {
        return true;
    }
    
    return true;
}

void BaseDialog::onTouchMoved(Touch*touch, cocos2d::Event *event) {
}

void BaseDialog::onTouchEnded(Touch*touch, cocos2d::Event *event) {
}