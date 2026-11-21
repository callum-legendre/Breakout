#ifndef BALLSCRIPT_H
#define BALLSCRIPT_H

#include "script.h"
#include "vector2.h"

class BallScript : public Script
{
    public:
    BallScript(GameObject* parent);
    void Update(float deltaTime) override;
    void OnCollision(ColliderComponent* thisCollider, ColliderComponent* otherCollider) override;

    private:
    float mTimer = 0.0f;
    int mSpeedIncreaseInterval = 10; // this is in seconds
    int mSpeed = 1;
    Vector2 mVelocity;
};

#endif
