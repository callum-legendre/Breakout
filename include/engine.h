#ifndef ENGINE_H
#define ENGINE_H



class Engine
{
    public:
        Engine();
        ~Engine();
        void Run();

    private:
    SDL_Renderer* mRender = nullptr;
    SDL_Window* mWindow = nullptr;
};

#endif
