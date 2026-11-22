#include "objectFactory.h"

#include "components/colliderComponent.h"
#include "components/inputComponent.h"
#include "scripts/ballscript.h"
#include "scripts/brickscript.h"
#include "scripts/paddlescript.h"

#include "gameObject.h"
#include "resourceManager.h"

ObjectFactory::ObjectFactory(ResourceManager* resourceManager)
{
    mResourceManager = resourceManager;
}

std::unique_ptr<GameObject> ObjectFactory::CreateBall()
{
    std::unique_ptr<GameObject> ball = std::make_unique<GameObject>(0, 0, 16, 16); // dimensions of the ball are 16x16, location is 0,0 because unknown

    ball->AddComponent<ColliderComponent>(ball);

    ball->AddScript<BallScript>(ball);

    return ball;
}

std::unique_ptr<GameObject> ObjectFactory::CreatePaddle()
{
    std::unique_ptr<GameObject> paddle = std::make_unique<GameObject>(0, 0, 86, 10); // dimensions of the paddle are 86x10, location does not matter because it will soon be overwritten by input

    paddle->AddComponent<ColliderComponent>(paddle);
    paddle->AddComponent<InputComponent>(paddle);

    paddle->AddScript<PaddleScript>(paddle);

    return paddle;
}

std::unique_ptr<GameObject> ObjectFactory::CreateBrick(int brickType, float x, float y)
{
    std::unique_ptr<GameObject> brick = std::make_unique<GameObject>(x, y, 32, 32); // bricks always are 32x32, positions decided before function call

    brick->AddComponent<ColliderComponent>(brick);
    brick->AddScript<BrickScript>(brick, brickType);

    if (brickType != -1){
        brick->AddComponent<SpriteComponent>(brick, mResourceManager->GetTexture("brickTexture"));
    }

    return brick;
}