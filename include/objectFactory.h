#ifndef OBJECTFACTORY_H
#define OBJECTFACTORY_H

#include <memory>

class GameObject;
class ResourceManager;

class ObjectFactory
{
    public:
    ObjectFactory(ResourceManager* resourceManager);
    ~ObjectFactory() = default;
    std::unique_ptr<GameObject> CreateBrick(int brickType, float x, float y, size_t* numBricks);
    std::unique_ptr<GameObject> CreateBall(GameObject* paddle);
    std::unique_ptr<GameObject> CreatePaddle();

    private:
    ResourceManager* mResourceManager;
    
};

#endif
