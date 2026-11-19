#include "gameObject.h"

#include <SDL3/SDL.h>

GameObject::GameObject(float xPos, float yPos, float width, float height)
{
    mTransform.x = xPos;
    mTransform.y = yPos;
    mTransform.w = width;
    mTransform.h = height;
}

SDL_FRect GameObject::GetTransform()
{
    return mTransform;
}

Vector2 GameObject::GetPosition()
{
    return Vector2(mTransform.x, mTransform.y);
}

void GameObject::SetPosition(Vector2 newPos)
{
    mTransform.x = newPos.x;
    mTransform.y = newPos.y;
}

void GameObject::MovePosition(Vector2 direction)
{
    mTransform.x += direction.x;
    mTransform.y += direction.y;
}
