#include "scripts/paddlescript.h"
#include "gameObject.h"
#include "vector2.h"
#include "playerInput.h"
#include "components/colliderComponent.h"
#include "scripts/ballscript.h"
#include "scripts/brickscript.h"

#include <SDL3/SDL.h>

PaddleScript::PaddleScript(GameObject* parent) : Script(parent) {}

void PaddleScript::Update(float)
{
    SDL_FRect paddleTransform = mParent->GetTransform();

    Vector2 centerPaddle = Vector2(mInput.mousePos.x - (paddleTransform.w / 2), paddleTransform.y);

    mParent->SetPosition(centerPaddle);
}

void PaddleScript::OnCollision(ColliderComponent* thisCollider, ColliderComponent* otherCollider)
{
    BallScript* ballScript = otherCollider->GetParent()->GetScript<BallScript>();
    BrickScript* brickScript = otherCollider->GetParent()->GetScript<BrickScript>();
    if (ballScript){
        SDL_FRect paddleTransform = thisCollider->GetColliderRect();
        Vector2 centerPaddle = Vector2(paddleTransform.x + (paddleTransform.w / 2), paddleTransform.y + (paddleTransform.h / 2));

        SDL_FRect ballTransform = otherCollider->GetColliderRect();
        Vector2 centerBall = Vector2(ballTransform.x + (ballTransform.w / 2), ballTransform.y + (ballTransform.h / 2));

        Vector2 paddleToBall = Distance(centerBall, centerPaddle);
        float dotProduct = Dot(Vector2(1,0), paddleToBall);

        Vector2* velocity = ballScript->GetVelocity();

        velocity->x = 10 * dotProduct;
    }
    else if (brickScript){
        SDL_FRect brickTransform = otherCollider->GetColliderRect();
        SDL_FRect paddleTransform = thisCollider->GetColliderRect();

        if (paddleTransform.x <= brickTransform.w){
            mParent->SetPosition(Vector2(brickTransform.x + brickTransform.w, paddleTransform.y));
        }
        else {
            mParent->SetPosition(Vector2(brickTransform.x - paddleTransform.w, paddleTransform.y));
        }
    }

}
