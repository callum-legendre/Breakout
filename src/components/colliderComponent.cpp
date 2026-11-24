#include "components/colliderComponent.h"

#include <SDL3/SDL.h>
#include "script.h"
#include "gameObject.h"

ColliderComponent::ColliderComponent(GameObject* parent) : Component(parent) {}

bool ColliderComponent::CheckCollision(ColliderComponent* otherCollider)
{
    SDL_FRect thisTransform = mParent->GetTransform();
    SDL_FRect otherTransform = otherCollider->GetParent()->GetTransform();
    
    if (SDL_HasRectIntersectionFloat(&thisTransform, &otherTransform)){
        
        mParent->CallScripts(&Script::OnCollision, this, otherCollider);

        return true;
    }
    
    return false;
}

SDL_FRect ColliderComponent::GetColliderRect()
{
    return mParent->GetTransform();
}
