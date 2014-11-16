//
//  LayoutHelper.cpp
//  ChessExplorer
//
//  Created by Jamie Yung on 28/07/2014.
//
//

#include "LayoutHelper.h"

float LayoutHelper::getLevelButtonSize() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    float ret = visibleSize.height/20
    ;
    return ret;
}

float LayoutHelper::getTitleFontSize() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    float ret = visibleSize.height/24;
    return ret;
}

float LayoutHelper::getNormalFontSize() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    float ret = visibleSize.height/26;
    return ret;
}

float LayoutHelper::getDialogEdgeMargin() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    float ret = visibleSize.height/64;
    return ret;
}

float LayoutHelper::getDialogInnerMargin() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    float ret = visibleSize.height/64;
    return ret;
}

float LayoutHelper::getButtonMargin() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    float ret = visibleSize.height/48;
    return ret;
}