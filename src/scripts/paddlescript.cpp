#include "scripts/paddlescript.h"
#include "gameObject.h"
#include "vector2.h"
#include "playerInput.h"

#include <SDL3/SDL.h>

PaddleScript::PaddleScript(GameObject* parent) : Script(parent) {}

void PaddleScript::Update(float)
{
    SDL_FRect paddleTransform = mParent->GetTransform();

    Vector2 centerPaddle = Vector2(mInput.mousePos.x - (paddleTransform.w / 2), paddleTransform.y);

    mParent->SetPosition(centerPaddle);
}
