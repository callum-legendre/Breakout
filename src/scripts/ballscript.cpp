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
    if (mOnPaddle == true){
        SDL_FRect paddleTransform = mPaddleReference->GetTransform();
        SDL_FRect ballTransform = mParent->GetTransform();

        Vector2 centeredBall = Vector2(paddleTransform.x + (paddleTransform.w - ballTransform.w) / 2, paddleTransform.y - ballTransform.h);

        mParent->SetPosition(centeredBall);

        if (mInput.lMouseClick == true){
            mVelocity = Vector2(500, 100);
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

    if (intersection.w > intersection.h){ // if it collided with a horizontal edge, negate the y of velocity

        bool above = false;
        if (thisRect.y + thisRect.h / 2.0f < otherRect.y + otherRect.h / 2.0f){
            above = true;
        }

        if (above){
            thisRect.y = otherRect.y - thisRect.h;
        }
        else {
            thisRect.y = otherRect.y + otherRect.h;
        }

        mVelocity.y = -mVelocity.y;
    }
    else { // otherwise it collided with the verticle edge, so negate the x

        bool left = false;
        if (thisRect.x + thisRect.w / 2.0f < otherRect.x + otherRect.w / 2.0f){
            left = true;
        }

        if (left){
            thisRect.x = otherRect.x - thisRect.w;
        }
        else {
            thisRect.x = otherRect.x + otherRect.w;
        }

        mVelocity.x = -mVelocity.x;
    }

    Vector2 newPos = Vector2(thisRect.x, thisRect.y);
    mParent->SetPosition(newPos); // move the ball out of the object it is colliding with
}
