//
//  LayoutHelper.h
//  ChessExplorer
//
//  Created by Jamie Yung on 28/07/2014.
//
//

#ifndef __ChessExplorer__LayoutHelper__
#define __ChessExplorer__LayoutHelper__

#include "cocos2d.h"

USING_NS_CC;

class LayoutHelper {
public:
    static float getLevelButtonSize();
    static float getTitleFontSize();
    static float getNormalFontSize();
    static float getDialogEdgeMargin();
    static float getDialogInnerMargin();
    static float getButtonMargin();
};

#endif /* defined(__ChessExplorer__LayoutHelper__) */
