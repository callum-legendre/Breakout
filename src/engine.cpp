#include <SDL3/SDL.h>
#include "engine.h"

Engine::Engine()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO); // can move init into main if we get strange segfaults
    mWindow = SDL_CreateWindow("Breakout", 640, 480, SDL_WINDOW_ALWAYS_ON_TOP);
    mRender = SDL_CreateRenderer(mWindow, nullptr);
}

Engine::~Engine()
{
    SDL_DestroyRenderer(mRender);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Engine::Run()
{
    mRunning = true;

    while (mRunning = true){
        std::sleep(10);
        mRunning = false;
    }
}

