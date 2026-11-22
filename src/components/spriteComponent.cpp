#include "components/spriteComponent.h"
#include <SDL3/SDL3.h>

SpriteComponent::SpriteComponent(GameObject* parent, SDL_Texture* texture) : Component(parent)
{
    mSpriteTexture = texture;
}

SDL_Texture* SpriteComponent::GetTexture()
{
    return mSpriteTexture;
}
