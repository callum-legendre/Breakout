#include "engine.h"
#include <iostream>


Engine::Engine()
{
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO); // can move init into main if we get strange segfaults
    mWindow = SDL_CreateWindow("Breakout", 640, 480, SDL_WINDOW_ALWAYS_ON_TOP);
    mRenderer = SDL_CreateRenderer(mWindow, nullptr);
}

Engine::~Engine()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Engine::Run()
{
    mRunning = true;

    while (mRunning == true){

        Input();
        Update();
        Render();
    }
}

void Engine::Input()
{
    SDL_Event event;

    while(SDL_PollEvent(&event)){

        switch (event.type)
        {
        case SDL_EVENT_QUIT:
            mRunning = false;
            break;
        
        default:
            break;
        }
    }
}

void Engine::Update()
{
    // update behavior will go here
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE); 
    // 0,0,0 is black
    // SDL_ALPHA_OPAQUE is the colour that SDL should make transparent, this corresponds to the funny grid thingy in pngs

    SDL_RenderClear(mRenderer);

    // render objects here

    SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    // 255, 255, 255 sets the color to white
    SDL_RenderDebugText(mRenderer, 0, 0, "testing 1 2 3"); // temporary for testing

    SDL_RenderPresent(mRenderer);
}

