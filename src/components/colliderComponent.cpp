#include "components/physicsComponent.h"

#include <SDL3/SDL3.h>

ColliderComponent::ColliderComponent(GameObject* parent) : Component(parent) {}

void ColliderComponent::CheckCollision(SDL_FRect otherTransform)
{
    mCollision = SDL_HasRectIntersectionFloat(mParent->GetTransform(), otherTransform);
}

bool ColliderComponent::HasCollision()
{
    return mCollision;
}
