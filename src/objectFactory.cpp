#include "objectFactory.h"

#include "components/colliderComponent.h"
#include "components/inputComponent.h"
#include "components/spriteComponent.h"
#include "scripts/ballscript.h"
#include "scripts/brickscript.h"
#include "scripts/paddlescript.h"

#include "gameObject.h"
#include "resourceManager.h"

ObjectFactory::ObjectFactory(ResourceManager* resourceManager)
{
    mResourceManager = resourceManager;
}

std::unique_ptr<GameObject> ObjectFactory::CreateBall(GameObject* paddle)
{
    SpriteInfo ballInfo = mResourceManager->GetTexture("ball");

    std::unique_ptr<GameObject> ball = std::make_unique<GameObject>(0, 0, ballInfo.spriteWidth, ballInfo.spriteHeight); // dimensions of the ball are 16x16, location is 0,0 because unknown

    ball->AddComponent<ColliderComponent>(ball.get());

    ball->AddComponent<SpriteComponent>(ball.get(), ballInfo);

    ball->AddComponent<InputComponent>(ball.get());

    ball->AddScript<BallScript>(ball.get(), paddle);

    return ball;
}

std::unique_ptr<GameObject> ObjectFactory::CreatePaddle()
{
    SpriteInfo paddleInfo = mResourceManager->GetTexture("paddle");

    std::unique_ptr<GameObject> paddle = std::make_unique<GameObject>(320, 470, paddleInfo.spriteWidth, paddleInfo.spriteHeight); // dimensions of the paddle are 86x10, location does not matter because it will soon be overwritten by input

    paddle->AddComponent<ColliderComponent>(paddle.get());
    paddle->AddComponent<InputComponent>(paddle.get());
    paddle->AddComponent<SpriteComponent>(paddle.get(), paddleInfo);

    paddle->AddScript<PaddleScript>(paddle.get());

    return paddle;
}

std::unique_ptr<GameObject> ObjectFactory::CreateBrick(int brickType, float x, float y)
{
    SpriteInfo brickInfo = mResourceManager->GetTexture("brick");

    std::unique_ptr<GameObject> brick = std::make_unique<GameObject>(x, y, brickInfo.spriteWidth, brickInfo.spriteHeight); // bricks always are 32x32, positions decided before function call

    brick->AddComponent<ColliderComponent>(brick.get());
    brick->AddScript<BrickScript>(brick.get(), brickType);

    if (brickType != -1){
        brick->AddComponent<SpriteComponent>(brick.get(), brickInfo);
    }
    else {
        brick->AddComponent<SpriteComponent>(brick.get(), mResourceManager->GetTexture("wall"));
    }

    return brick;
}