//
//  CircleEntity.h
//  Cocosnauts
//
//  Created by Jamie Yung on 16/11/2014.
//
//

#ifndef __Cocosnauts__CircleEntity__
#define __Cocosnauts__CircleEntity__

#include "Entity.h"

class CircleEntity : public Entity {
public:
    virtual bool init();
    CREATE_FUNC(CircleEntity);
    
    bool intersect(Entity*other);
    float getUnitOrbitRadius();
    
    void setColor(const Color3B& col);
    
private:
    Sprite*sprite;
};

#endif /* defined(__Cocosnauts__CircleEntity__) */
