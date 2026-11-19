#ifndef ENGINE_H
#define ENGINE_H



class Engine
{
    public:
        Engine();
        ~Engine();
        void Run();

    private:

    // -- sdl referenes --
    SDL_Renderer* mRender = nullptr;
    SDL_Window* mWindow = nullptr;

    // -- engine propoerties -- 
    bool mRunning = false;
};

#endif
