#include "components/colliderComponent.h"

#include <SDL3/SDL3.h>
#include "script.h"

ColliderComponent::ColliderComponent(GameObject* parent) : Component(parent) {}

void ColliderComponent::CheckCollision(ColliderComponent* otherCollider)
{

    if (SDL_HasRectIntersectionFloat(mParent->GetTransform(), otherCollider->GetParent()->GetTransform())){
        
        mParent->CallScripts(&Script::OnCollision, *this, otherCollider);
    }

    
}

SDL_FRect ColliderComponent::GetColliderRect()
{
    return mParent->GetTransform();
}
