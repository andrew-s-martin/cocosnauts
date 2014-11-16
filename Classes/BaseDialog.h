//
//  BaseDialog.h
//  ChessExplorer
//
//  Created by Jamie Yung on 21/07/2014.
//
//

#ifndef __ChessExplorer__BaseDialog__
#define __ChessExplorer__BaseDialog__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "Button.h"

USING_NS_CC;

class BaseDialog : public cocos2d::Layer {
public:
    CREATE_FUNC(BaseDialog);
    virtual bool init();
    void setDismissNotificationString(std::string str);
    void setAnimateShowDismiss(bool animate);
    virtual void show();
    virtual void dismiss();
    void setTitleString(std::string str);
    Rect getContentBoundingBox() const;
protected:
    virtual void adjustSize();
    bool onTouchBegan(Touch*touch, Event*event);
    void onTouchMoved(Touch*touch, Event*event);
    void onTouchEnded(Touch*touch, Event*event);
    
    float edgeMargin, innerMargin, titleBarHeight;
    std::string _dismissNotificationString;
    bool _animateShowDismiss;
    EventListenerTouchOneByOne*listener;
    extension::Scale9Sprite*box;
    Label*_title;
    NSC::ui::Button*_closeButton;
};

#endif /* defined(__ChessExplorer__BaseDialog__) */
