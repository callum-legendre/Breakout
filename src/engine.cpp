#include "engine.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include <cmath>
#include <algorithm>

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

    SDL_MouseButtonFlags state = SDL_GetMouseState(&mInput.mousePos.x, &mInput.mousePos.y);
    mInput.lMouseClick = (state & SDL_BUTTON_LMASK);
    mInput.rMouseClick = (state & SDL_BUTTON_RMASK);

    mPaddle->GetComponent<InputComponent>()->SetInput(mInput);

    for (auto& ball : mBalls){
        if (ball){
            ball->GetComponent<InputComponent>()->SetInput(mInput);
        }
    }
}

void Engine::Update()
{
    if (mPlayerLive){
        UpdateScripts();
        UpdateColliders();
        LateUpdateScripts();
        UpdateDestruction();
        UpdateGameState();
    }
    else {
        if (mInput.rMouseClick){
            mPlayerLive = true;
            mCurrentLevelNum = 0;
            mPlayerScore = 0;
            LoadLevel();

            mBalls.push_back(mObjectFactory->CreateBall(mPaddle.get()));
            mBallCount++;
        }
    }
}

void Engine::UpdateScripts()
{
    mPaddle->CallScripts(&Script::Update, mFixedUpdateTime);
    for (const auto& ball : mBalls){
        if (ball){
            ball->CallScripts(&Script::Update, mFixedUpdateTime);

            if (ball->GetPosition().y > mWindowHeight){
                ball->Destroy();
            }
        }
    }
}

void Engine::UpdateColliders()
{
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

                    if (brickCollider->CheckCollision(ballCollider) && brickCollider->GetParent()->GetType() == "brick"){
                        mPlayerScore += 20;
                    }
                    ballCollider->CheckCollision(brickCollider);
                }
            }
        }

        // check collision with the paddle
        ColliderComponent* paddleCollider = mPaddle->GetComponent<ColliderComponent>();
        paddleCollider->CheckCollision(ballCollider);
        ballCollider->CheckCollision(paddleCollider);   
    }

    for (const auto& brick : mCurrentLevelBlocks.back()){
        if (brick){
            ColliderComponent* paddleCollider = mPaddle->GetComponent<ColliderComponent>();
            paddleCollider->CheckCollision(brick->GetComponent<ColliderComponent>());
        }
    }
}

void Engine::LateUpdateScripts()
{
    mPaddle->CallScripts(&Script::LateUpdate, mFixedUpdateTime);
    for (const auto& ball : mBalls){
        if (ball){
            ball->CallScripts(&Script::LateUpdate, mFixedUpdateTime);

            if (ball->GetPosition().y > mWindowHeight){
                ball->Destroy();
            }
        }
    }
}

void Engine::UpdateDestruction()
{
    // check balls
    for (auto& ball : mBalls){
        if (ball && ball->GetAlive() == false){
            ball.reset();
            mBallCount--;
        }

    }

    // check bricks
    for (auto& row : mCurrentLevelBlocks){
        for (auto& brick : row){
            if (brick && brick->GetAlive() == false){
                brick.reset();
                mNumBlocks--;
            }
        }
    }
}

void Engine::UpdateGameState()
{
    if (mBallCount == 0){
        mPlayerLive = false;
    }
    else if (mNumBlocks == 0){

        if (mLoadTimer == 0){
            mCurrentLevelNum++;

            for (auto& ball : mBalls){
                ball.reset();
            }

            mLoadTimer += mFixedUpdateTime;
        }
        else if (mLoadTimer < mLoadTime){
            mLoadTimer += mFixedUpdateTime;
        }
        else {

            LoadLevel();

            mBalls.push_back(mObjectFactory->CreateBall(mPaddle.get()));
            mBallCount = 1;
            mLoadTimer = 0;
        }
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

    if (mPlayerLive && mLoadTimer >= 0){
        std::string scoreText = "Score: ";
        scoreText.append(std::to_string(mPlayerScore));
        SDL_RenderDebugText(mRenderer, 10, 10, scoreText.c_str());

        std::string levelText = "Level ";
        levelText.append(std::to_string(mCurrentLevelNum + 1));
        SDL_RenderDebugText(mRenderer, mWindowWidth - 100, 10, levelText.c_str());

        if (mPlayerLive && mLoadTimer > 0){
            float oldScaleX;
            float oldScaleY;
            SDL_GetRenderScale(mRenderer, &oldScaleX, &oldScaleY);

            float scale = 3;
            SDL_SetRenderScale(mRenderer, scale, scale);

            std::string completedText = "Level ";
            completedText.append(std::to_string(mCurrentLevelNum));
            completedText.append(" completed!");
            SDL_RenderDebugText(mRenderer, 50 / scale, 50 / scale, completedText.c_str());

            SDL_SetRenderScale(mRenderer, oldScaleX, oldScaleY);
        }
    }
    else if (!mPlayerLive){
        float oldScaleX;
        float oldScaleY;
        SDL_GetRenderScale(mRenderer, &oldScaleX, &oldScaleY);

        float scale = 3;
        SDL_SetRenderScale(mRenderer, scale, scale);

        SDL_RenderDebugText(mRenderer, 50 / scale, 50 / scale, "GAME OVER");
        SDL_RenderDebugText(mRenderer, 50 / scale, 100 / scale, "Right Click to restart");

        scale = 2;
        SDL_SetRenderScale(mRenderer, scale, scale);

        std::string scoreText = "Your score was: ";
        scoreText.append(std::to_string(mPlayerScore));
        SDL_RenderDebugText(mRenderer, 50 / scale, 250 / scale, scoreText.c_str());

        SDL_SetRenderScale(mRenderer, oldScaleX, oldScaleY);
    }

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
                newRow.push_back(mObjectFactory->CreateBrick(layoutArray[row][col], col * 32, row * 32, &mNumBlocks));
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

