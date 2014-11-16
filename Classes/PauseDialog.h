//
//  PauseDialog.h
//  ChessExplorer
//
//  Created by Jamie Yung on 24/07/2014.
//
//

#ifndef __ChessExplorer__PauseDialog__
#define __ChessExplorer__PauseDialog__

#include "BaseDialog.h"
#include "Button.h"

USING_NS_CC;

class PauseDialog : public BaseDialog {
public:
    CREATE_FUNC(PauseDialog);
    virtual bool init();
private:
    void adjustSize();
    bool onTouchBegan(Touch*touch, Event*event);
    void onTouchMoved(Touch*touch, Event*event);
    void onTouchEnded(Touch*touch, Event*event);
    
    NSC::ui::Button*_toMenu;
};


#endif /* defined(__ChessExplorer__PauseDialog__) */
