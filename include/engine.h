#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <iostream>
#include <memory>
#include <SDL3/SDL.h>
#include "playerInput.h"

class ResourceManager;
class GameObject;
class ObjectFactory;

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
        void UpdateScripts();
        void UpdateColliders();
        void LateUpdateScripts();
        void UpdateDestruction();
        void UpdateGameState();
    void Render();

    // -- sdl referenes --
    SDL_Renderer* mRenderer = nullptr;
    SDL_Window* mWindow = nullptr;

    // -- engine proporties -- 
    bool mRunning = false;
    size_t mWindowWidth = 0;
    size_t mWindowHeight = 0;
    float mFixedUpdateTime = 1.0f/120.0f;

    // -- manager and factory --
    std::unique_ptr<ObjectFactory> mObjectFactory;
    std::unique_ptr<ResourceManager> mResourceManager;

    // -- level properties and methods -- 
    void LoadLevel();
    size_t mCurrentLevelNum = 0;
    size_t mNumBlocks = 0;
    std::vector<std::vector<std::unique_ptr<GameObject>>> mCurrentLevelBlocks;
    std::unique_ptr<GameObject> mPaddle;
    std::vector<std::unique_ptr<GameObject>> mBalls;
    size_t mPlayerScore = 0;
    size_t mBallCount = 0;
    bool mPlayerLive = true;
    PlayerInput mInput;
};

#endif
