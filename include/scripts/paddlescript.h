#ifndef PADDLESCRIPT_H
#define PADDLESCRIPT_H

#include "script.h"

class PaddleScript : public Script
{
    public:
    PaddleScript(GameObject* parent);
    void Update(float) override;
    void OnCollision(ColliderComponent* thisCollider, ColliderComponent* otherCollider) override;
};

#endif
