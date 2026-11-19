#ifndef ENGINE_H
#define ENGINE_H

#include <SDL3/SDL.h>


class Engine
{
    public:
        Engine();
        ~Engine();
        void Run();


    private:
    
    // -- frame loop functions --
    void Input();
    void Update();
    void Render();

    // -- sdl referenes --
    SDL_Renderer* mRenderer = nullptr;
    SDL_Window* mWindow = nullptr;

    // -- engine propoerties -- 
    bool mRunning = false;
};

#endif
