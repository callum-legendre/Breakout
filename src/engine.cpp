#include "engine.h"

#include <nlohmann/json.hpp>
#include <fstream>

#include "resourceManager.h"
#include "gameObject.h"
#include "objectFactory.h"

Engine::Engine()
{
    mWindowWidth = 640;
    mWindowHeight = 480;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO); // can move init into main if we get strange segfaults
    mWindow = SDL_CreateWindow("Breakout", mWindowWidth, mWindowHeight, SDL_WINDOW_ALWAYS_ON_TOP);
    mRenderer = SDL_CreateRenderer(mWindow, nullptr);

    mResourceManager = std::make_unique<ResourceManager>(mRenderer, "resources.json");
    mObjectFactory = std::make_unique<ObjectFactory>(mResourceManager.get());

    LoadLevel();
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

void Engine::LoadLevel()
{
    // get the filepath to json and parse it
    std::string levelPath = mResourceManager->GetLevelPath(mCurrentLevelNum);
    std::ifstream file(levelPath.c_str());
    nlohmann::json levelFile = nlohmann::json::parse(file);

    // get values of importance from the json
    const auto& layoutArray = levelFile.at("layout");
    size_t numRows = levelFile.at("rows");
    size_t numCols = levelFile.at("columns");

    // create the new level grid
    std::vector<std::vector<std::unique_ptr<GameObject>>> newLevel;
    newLevel.reserve(numRows);
    for (size_t row = 0; row < numRows; row++){
        std::vector<std::unique_ptr<GameObject>> newRow;
        newRow.reserve(numCols);
        for (size_t col = 0; col < numCols; col++){
            newRow.push_back(mObjectFactory->CreateBrick(layoutArray[row][col], row * 32, col * 32));
        }
        newLevel.push_back(std::move(newRow));
    }

    // assign new level grid to the current level member
    mCurrentLevelBlocks = std::move(newLevel);
}

