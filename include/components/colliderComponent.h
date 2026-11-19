#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include "component.h"

struct SDL_FRect;

class ColliderComponent : public Component
{
    public:
    ColliderComponent(GameObject* parent);
    void CheckCollision(SDL_FRect otherCollider);
    bool HasCollision();

    private:
    bool mCollision = false;
    
};

#endif
