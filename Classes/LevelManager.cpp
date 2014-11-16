//
//  LevelManager.cpp
//  Cocosnauts
//
//  Created by Jamie Yung on 15/11/2014.
//
//

#include "LevelManager.h"
#include "LevelScene.h"
#include "MenuScene.h"

const std::string LevelManager::getJsonString(int level) {
    std::stringstream ss;
    ss << level;
    return "Level" + ss.str() + ".json";
}

void LevelManager::goNextLevel(int curLevel) {
    auto nextString = LevelManager::getJsonString(curLevel + 1);
    auto utils = FileUtils::getInstance();
    Scene* scene;
    if (!utils->isFileExist(nextString)) {
        scene = MenuScene::createScene();
    } else {
        scene = LevelScene::createScene(++curLevel);
    }
    Director::getInstance()->replaceScene(scene);
}