#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include "component.h"

struct SDL_FRect;

class ColliderComponent : public Component
{
    public:
    ColliderComponent(GameObject* parent);
    bool CheckCollision(ColliderComponent* otherCollider);
    SDL_FRect GetColliderRect();
};

#endif
