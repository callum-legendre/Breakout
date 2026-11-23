#include "components/spriteComponent.h"
#include "resourceManager.h"
#include "gameObject.h"
#include <SDL3/SDL.h>

SpriteComponent::SpriteComponent(GameObject* parent, SpriteInfo info) : Component(parent)
{
    mTexture = info.texture;

    for (float j = 0; j < info.textureHeight; j += info.spriteHeight){
        for (float i = 0; i < info.textureWidth; i += info.spriteWidth){
            SDL_FRect frame = {i, j, info.spriteWidth, info.spriteHeight};
            mFrames.push_back(frame);
        }
    }

    mCurrentFrame = 0;
}

void SpriteComponent::Render(SDL_Renderer* renderer)
{
    SDL_FRect transform = mParent->GetTransform();
    SDL_RenderTexture(renderer, mTexture, &mFrames[mCurrentFrame], &transform);
}

void SpriteComponent::ChangeFrame(int newFrame)
{
    mCurrentFrame = newFrame;
}
