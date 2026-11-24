#include "engine.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include <cmath>

#include "resourceManager.h"
#include "gameObject.h"
#include "components/inputComponent.h"
#include "components/colliderComponent.h"
#include "components/spriteComponent.h"
#include "objectFactory.h"
#include "script.h"

Engine::Engine()
{
    mWindowWidth = 704;
    mWindowHeight = 512;

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO); // can move init into main if we get strange segfaults
    mWindow = SDL_CreateWindow("Breakout", mWindowWidth, mWindowHeight, SDL_WINDOW_ALWAYS_ON_TOP);
    mRenderer = SDL_CreateRenderer(mWindow, nullptr);

    mResourceManager = std::make_unique<ResourceManager>(mRenderer, "resources.json");
    mObjectFactory = std::make_unique<ObjectFactory>(mResourceManager.get());

    LoadLevel();

    mPaddle = mObjectFactory->CreatePaddle();
    mBalls.push_back(mObjectFactory->CreateBall(mPaddle.get()));
    mBallCount++;
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

    float accumulatedTime = 0.0f;

    int previousTime = 0;
    int currentTime = 0;

    while (mRunning == true){

        Input();

        currentTime = SDL_GetTicks();
        accumulatedTime += static_cast<float>(currentTime - previousTime) / 1000; // this converts into seconds from milliseconds
        while (accumulatedTime >= mFixedUpdateTime){
            Update();
            accumulatedTime -= mFixedUpdateTime;
        }
        previousTime = currentTime;

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

    PlayerInput input;
    SDL_MouseButtonFlags state = SDL_GetMouseState(&input.mousePos.x, &input.mousePos.y);
    input.lMouseClick = (state & SDL_BUTTON_LMASK);

    mPaddle->GetComponent<InputComponent>()->SetInput(input);

    for (auto& ball : mBalls){
        if (ball){
            ball->GetComponent<InputComponent>()->SetInput(input);
        }
    }
}

void Engine::Update()
{
    // update scripts
    mPaddle->CallScripts(&Script::Update, mFixedUpdateTime);
    for (const auto& ball : mBalls){
        if (ball){
            ball->CallScripts(&Script::Update, mFixedUpdateTime);

            if (ball->GetPosition().y > mWindowHeight){
                ball->Destroy();
            }
        }
    }

    // check for collisions
    for (const auto& ball : mBalls){

        if (!ball){
            continue;
        }

        SDL_FRect ballTransform = ball->GetTransform();

        // get the posititions of the ball but converted into the tile grid that we have
        Vector2 topLeft = Vector2(std::floor(ballTransform.x / 32.0f), std::floor(ballTransform.y / 32.0f));
        Vector2 topRight = Vector2(std::floor((ballTransform.x + ballTransform.w) / 32.0f), std::floor(ballTransform.y / 32.0f));
        Vector2 bottomLeft = Vector2(std::floor(ballTransform.x / 32.0f), std::floor((ballTransform.y + ballTransform.h) / 32.0f));
        Vector2 bottomRight = Vector2(std::floor((ballTransform.x + ballTransform.w) / 32.0f), std::floor((ballTransform.y + ballTransform.h) / 32.0f));

        // adds the unique grids to a list of unique grids
        // this is to avoid calling collision checks on a one square 4 times
        std::vector<Vector2> uniqueGrids;
        for (const Vector2& value : {topLeft, topRight, bottomLeft, bottomRight}){
            if (std::find(uniqueGrids.begin(), uniqueGrids.end(), value) == uniqueGrids.end()){
                uniqueGrids.push_back(value);
            }
        }

        // get the ball's collider
        ColliderComponent* ballCollider = ball->GetComponent<ColliderComponent>();

        // check collisions in that grid
        for (Vector2& grid : uniqueGrids){

            int row = static_cast<int>(grid.y);
            int col = static_cast<int>(grid.x);

            if ((row >= 0 && row < static_cast<int>(mCurrentLevelBlocks.size())) && (col >= 0 && col < static_cast<int>(mCurrentLevelBlocks[row].size()))){

                if (mCurrentLevelBlocks[row][col] != nullptr){
                    ColliderComponent* brickCollider = mCurrentLevelBlocks[row][col]->GetComponent<ColliderComponent>();

                    brickCollider->CheckCollision(ballCollider);
                    ballCollider->CheckCollision(brickCollider);
                }
            }
        }

        // check collision with the paddle
        ColliderComponent* paddleCollider = mPaddle->GetComponent<ColliderComponent>();
        paddleCollider->CheckCollision(ballCollider);
        ballCollider->CheckCollision(paddleCollider);
    }

    // destroy objects
    for (auto& ball : mBalls){
        if (ball && ball->GetAlive() == false){
            ball.reset();
            mBallCount--;
        }

    }

    for (auto& row : mCurrentLevelBlocks){
        for (auto& brick : row){
            if (brick && brick->GetAlive() == false){
                brick.reset();
            }
        }
    }

    // check if the game should end
    if (mBallCount == 0){
        mRunning = false;
    }
}

void Engine::Render()
{
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE); 
    // 0,0,0 is black
    // SDL_ALPHA_OPAQUE is the colour that SDL should make transparent, this is set to the standard png tansparent one

    SDL_RenderClear(mRenderer);

    // render objects here
    mPaddle->GetComponent<SpriteComponent>()->Render(mRenderer);
    
    for (const auto& ball : mBalls){
        if (ball){
            ball->GetComponent<SpriteComponent>()->Render(mRenderer);
        }
    }

    for (const auto& row : mCurrentLevelBlocks){
        for (const auto& brick : row){
            if (brick){
                SpriteComponent* sprite = brick->GetComponent<SpriteComponent>();
                if (sprite){
                    sprite->Render(mRenderer);
                }
            }
        }
    }

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
            if (layoutArray[row][col] != 0){
                newRow.push_back(mObjectFactory->CreateBrick(layoutArray[row][col], col * 32, row * 32));
            }
            else {
                newRow.push_back(nullptr);
            }
        }
        newLevel.push_back(std::move(newRow));
    }

    // assign new level grid to the current level member
    mCurrentLevelBlocks = std::move(newLevel);
}

