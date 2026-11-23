#include "ballscript.h"
#include "gameObject.h"
#include "components/colliderComponent.h"

#include <SDL3/SDL.h>

BallScript::BallScript(GameObject* parent) : Script(parent) 
{
    mVelocity = Vector2(0, 0);
}

void BallScript::Update(float deltaTime) 
{
    // handle speed
    if (mTimer >= mSpeedIncreaseInterval){
        mSpeed++;
        mTimer = 0.0f;
    }
    else {
        mTimer += deltaTime;
    }

    // move the ball
    mParent->MovePosition(mVelocity * speed * delaTime);
}

void BallScript::OnCollision(ColliderComponent* thisCollider, ColliderComponent* otherCollider)
{
    SDL_FRect intersection;
    SDL_FRect thisRect = thisCollider->GetColliderRect()
    SDL_FRect otherRect = otherCollider->GetColliderRect()
    SDL_GetRectIntersectionFloat(&thisRect, &otherRec, &intersection);

    if (intersection.w > intersection.h){ // if it collided with a horizontal edge, negate the y of velocity
        mVelocity.y = -mVelocity.y;
        Vector2 newPos = Vector2(thisRect.x + intersection.w, thisRect.y);
        mParent->SetPosition(newPos); // move the ball out of the object it is colliding with
    }
    else { // otherwise it collided with the verticle edge, so negate the x
        mVelocity.x = -mVelocity.x;
        Vector2 newPos = Vector2(thisRect.x, thisRect.y + intersection.h);
        mParent->SetPosition(newPos); // move the ball out of the object it is colliding with
    }
}
