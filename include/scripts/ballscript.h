#ifndef BALLSCRIPT_H
#define BALLSCRIPT_H

#include "script.h"
#include "vector2.h"

#include <vector>
#include <SDL3/SDL.h>

class BallScript : public Script
{
    public:
    BallScript(GameObject* parent, GameObject* paddle);
    void Update(float deltaTime) override;
    void OnCollision(ColliderComponent* thisCollider, ColliderComponent* otherCollider) override;
    Vector2* GetVelocity();

    private:

    // -- update stuff --
    float mTimer = 0.0f;
    int mSpeedIncreaseInterval = 10; // this is in seconds
    int mSpeed = 1; // speed is a sclar multiplier for the velocity 
    Vector2 mVelocity; // velocity is a vector that is applied to the ball each frame
    bool mOnPaddle = true;
    GameObject* mPaddleReference;

    // -- collision stuff --
    bool mCollisionHappened = false;
    SDL_FRect mPreviousRect;
};

#endif
