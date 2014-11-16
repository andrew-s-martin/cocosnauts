//
//  LevelManager.cpp
//  Cocosnauts
//
//  Created by Jamie Yung on 15/11/2014.
//
//

#include "LevelManager.h"
#include "LevelScene.h"

const std::string LevelManager::getJsonString(int level) {
    std::stringstream ss;
    ss << level;
    return "Level" + ss.str() + ".json";
}

void LevelManager::goNextScene(int curLevel) {
    auto scene = LevelScene::createScene(++curLevel);
    Director::getInstance()->pushScene(scene);
}