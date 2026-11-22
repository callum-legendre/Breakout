#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "component.h"

struct SDL_Texture;

class SpriteComponent : public Component
{
    public:
    SpriteComponent(GameObject* parent, SDL_Texture* texture);
    SDL_Texture* GetTexture();

    private:
    SDL_Texture* mSpriteTexture;
};

#endif
