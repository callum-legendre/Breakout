#ifndef BRICKSCRIPT_H
#define BRICKSCRIPT_H

#include "script.h"

class BrickScript : public Script
{
    public:
    BrickScript(GameObject* parent, int health);
    void OnCollision(ColliderComponent*, ColliderComponent*) override;

    private:
    int mHealth;
};

#endif
