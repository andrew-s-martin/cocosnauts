//
//  ButtonFactory.cpp
//  ChessExplorer
//
//  Created by Jamie Yung on 13/11/2014.
//
//

#include "ButtonFactory.h"
#include "LayoutHelper.h"
#include "FontManager.h"
#include "extensions/cocos-ext.h"

NSC::ui::Button* ButtonFactory::createButton(const char* titleText) {
    auto fontSize = LayoutHelper::getNormalFontSize();
    
    auto ret = NSC::ui::Button::create("9_sprite_rounded.png", "9_sprite_rounded.png");
    ret->setPressedActionEnabled(true);
    ret->setScale9Enabled(true);
    ret->setTitleText(titleText);
    
    cocos2d::Label* temp = cocos2d::Label::createWithTTF(titleText, NSC::FontManager::getFontName(NSC::FontManager::ITALIC), fontSize);
    auto size = temp->getContentSize();
    auto textBuffer = fontSize;
    auto capInsetSize = 32;
    
    ret->setSize(Size(MAX(size.width + textBuffer, capInsetSize*2), MAX(size.height + textBuffer/2, capInsetSize*2)));
    ret->setColor(Color3B(197, 217, 115));
    return ret;
}