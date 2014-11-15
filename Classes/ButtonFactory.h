//
//  ButtonFactory.h
//  ChessExplorer
//
//  Created by Jamie Yung on 13/11/2014.
//
//

#ifndef __ChessExplorer__ButtonFactory__
#define __ChessExplorer__ButtonFactory__

#include "cocos2d.h"
#include "Button.h"

class ButtonFactory {
public:
    static NSC::ui::Button* createButton(const char* titleText);
};

#endif /* defined(__ChessExplorer__ButtonFactory__) */
