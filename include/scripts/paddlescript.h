#ifndef PADDLESCRIPT_H
#define PADDLESCRIPT_H

#include "script.h"

class PaddleScript : public Script
{
    public:
    PaddleScript(GameObject* parent);
    void Update(float deltaTime) override;
};

#endif
