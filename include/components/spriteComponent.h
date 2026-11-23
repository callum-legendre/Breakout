#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "component.h"
#include <vector>

struct SDL_Texture;
struct SDL_Renderer;
struct SDL_FRect;
struct SpriteInfo;

class SpriteComponent : public Component
{
    public:
    SpriteComponent(GameObject* parent, SpriteInfo info);
    void Render(SDL_Renderer* renderer);
    void ChangeFrame(int newFrame);

    private:
    SDL_Texture* mTexture;
    std::vector<SDL_FRect> mFrames;
    int mCurrentFrame;
};

#endif
