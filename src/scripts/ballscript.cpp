#include "scripts/ballscript.h"
#include "gameObject.h"
#include "components/colliderComponent.h"
#include "vector2.h"
#include "playerInput.h"

#include <SDL3/SDL.h>

BallScript::BallScript(GameObject* parent, GameObject* paddle) : Script(parent), mVelocity(0,0) 
{
    mPaddleReference = paddle;
}

void BallScript::Update(float deltaTime) 
{
    mPreviousRect = mParent->GetTransform();

    if (mOnPaddle == true){
        SDL_FRect paddleTransform = mPaddleReference->GetTransform();
        SDL_FRect ballTransform = mParent->GetTransform();

        Vector2 centeredBall = Vector2(paddleTransform.x + (paddleTransform.w - ballTransform.w) / 2, paddleTransform.y - ballTransform.h);

        mParent->SetPosition(centeredBall);

        if (mInput.lMouseClick == true){
            mVelocity = Vector2(100, 100);
            mOnPaddle = false;
        }
    }
    else {
        // handle speed
        if (mTimer >= mSpeedIncreaseInterval){
            mSpeed++;
            mTimer = 0.0f;
        }
        else {
            mTimer += deltaTime;
        }

        // move the ball
        mParent->MovePosition(mVelocity * mSpeed * deltaTime);
    }

    mCollisionHappened = false;
}

Vector2* BallScript::GetVelocity()
{
   return &mVelocity;
}

void BallScript::OnCollision(ColliderComponent* thisCollider, ColliderComponent* otherCollider)
{
    SDL_FRect intersection;
    SDL_FRect thisRect = thisCollider->GetColliderRect();
    SDL_FRect otherRect = otherCollider->GetColliderRect();
    SDL_GetRectIntersectionFloat(&thisRect, &otherRect, &intersection);

    if (mCollisionHappened){
        return;
    }
    else {
        mCollisionHappened = true;
    }

    if (mPreviousRect.x + mPreviousRect.w <= otherRect.x && thisRect.x + thisRect.w > otherRect.x){
        // crossed left edge
        mVelocity.x = -mVelocity.x;
        thisRect.x = otherRect.x - thisRect.w;
    }
    else if (mPreviousRect.x >= otherRect.x + otherRect.w && thisRect.x < otherRect.x + otherRect.w){
        // crossed right edge
        mVelocity.x = -mVelocity.x;
        thisRect.x = otherRect.x + otherRect.w;
    }
    else if (mPreviousRect.y + mPreviousRect.h <= otherRect.y && thisRect.y + thisRect.h > otherRect.y){
        // crossed top edge
        mVelocity.y = -mVelocity.y;
        thisRect.y = otherRect.y - thisRect.h;
    }
    else if (mPreviousRect.y >= otherRect.y + otherRect.h && thisRect.y < otherRect.y + otherRect.h){
        // crossed bottom edge
        mVelocity.y = -mVelocity.y;
        thisRect.y = otherRect.y + otherRect.h;
    }

    Vector2 newPos = Vector2(thisRect.x, thisRect.y);
    mParent->SetPosition(newPos); // move the ball out of the object it is colliding with
}
