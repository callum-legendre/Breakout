#ifndef ENGINE_H
#define ENGINE_H

#include <SDL3/SDL.h>
class ResourceManager;

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
    SDL_Renderer* mRenderer;
    SDL_Window* mWindow;

    // -- engine propoerties -- 
    bool mRunning = false;
    ResourceManager* mResourceManager;
};

#endif
