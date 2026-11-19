#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

struct SDL_FRect;
struct Vector2;
class Component;

#include <unordered_map>
#include <typeindex>
#include <memory>

class GameObject
{
    public:
    GameObject(float xPos, float yPos, float width, float height);
    ~GameObject() = default;

    // -- transform methods --
        // in this game it makes sense for each object to have an inherent position associated with it
        // which is why all of this in the base gameobject and not a transform component.
        // for the ease of scripting, move operations will be done using vectors that are applied to the SDL rectangle
    SDL_FRect GetTransform();
    void SetPosition(Vector2 newPos);
    void MovePosition(Vector2 direction);

    // -- component functions --
    template <typename ComponentType>
    ComponentType* GetComponent()
    {
        if (HasComponent<ComponentType>()){
            return static_cast<ComponentType*>(mComponents.at(typeid(ComponentType)));
        }
        else {
            return nullptr;
        }
    }

    template <typename ComponentType>
    bool HasComponent()
    {
        return mComponents.contains(typeid(ComponentType))
    }

    template <typename ComponentType, typename... Args>
    void AddComponent(Args&&... args)
    {
        // overwrites the index if there a component there already
        // this is intended, each object should only have one of each component, and the other functions are built on this assumption
        mComponents[typeid(ComponentType)] = std::make_unique<ComponentType>(std::forward<Args>(args));
    }

    // same as above with scripts

    private:
    SDL_FRect mTransform;
    std::unordered_map<std::type_index, std::unique_ptr<Component>> mComponents;
    // unordered map of scripts
};

#endif
