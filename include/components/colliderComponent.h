#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include "component.h"

struct SDL_FRect;

class ColliderComponent : public Component
{
    public:
    ColliderComponent(GameObject* parent);
    void CheckCollision(ColliderComponent* otherCollider);
};

#endif
