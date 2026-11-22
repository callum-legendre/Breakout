#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <iostream>
#include <memory>
#include <SDL3/SDL.h>
class ResourceManager;
class GameObject;
struct PlayerInput;

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

    // -- engine proporties -- 
    bool mRunning = false;
    size_t mWindowWidth = 0;
    size_t mWindowHeight = 0;
    ResourceManager* mResourceManager = nullptr;
    float mFixedUpdateTime = 1/60;

    // -- level properties and methods -- 
    void LoadLevel();
    size_t mCurrentLevelNum = 0;
    std::vector<std::vector<std::unique_ptr<GameObject>>> mCurrentLevelBlocks;
    std::unique_ptr<GameObject> mPaddle;
    std::vector<std::unique_ptr<GameObject>> mBalls;
    size_t mPlayerScore = 0;
};

#endif
