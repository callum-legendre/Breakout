#ifndef BRICKSCRIPT_H
#define BRICKSCRIPT_H

#include "script.h"

class BrickScript : public Script
{
    public:
    BrickScript(GameObject* parent);
    void OnCollision(ColliderComponent* thisCollider, ColliderComponent* otherCollider) override;
};

#endif
