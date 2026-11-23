#include "components/spriteComponent.h"
#include "resourceManager.h"
#include <SDL3/SDL3.h>

SpriteComponent::SpriteComponent(GameObject* parent, SpriteInfo info) : Component(parent)
{
    mSpriteTexture = info.texture;

    for (size_t j = 0; j < info.textureHeight; i += info.spriteHeight){
        for (size_t i = 0; i < info.textureWidth; i += info.spriteWidth){
            SDL_FRect frame = {i, j, info.spriteWidth, info.spriteHeight};
            mFrames.push_back(frame);
        }
    }

    mCurrentFrame = 0;
}

void SpriteComponent::Render(SDL_Renderer* renderer)
{
    SDL_RenderTexture(renderer, mTexture, mFrames[mCurrentFrame], mParent->GetTransform());
}

void SpriteComponent::ChangeFrame(int newFrame)
{
    mCurrentFrame = newFrame;
}
