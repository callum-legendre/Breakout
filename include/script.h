#ifndef SCRIPT_H
#define SCRIPT_H

#include "playerInput.h"

class GameObject;
class ColliderComponent;

class Script
{
    public:
    Script(GameObject* parent) {mParent = parent;}
    virtual ~Script() = default;
    virtual void OnCollision(ColliderComponent*, ColliderComponent*) {};
    virtual void Update(float) {};
    virtual void StoreInput(PlayerInput input) {mInput = input;} // was unsure about making this virtual or not, but i figure i may want to override this, so why not

    protected:
    GameObject* mParent;
    PlayerInput mInput;
};

#endif
