#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

struct SDL_FRect;
struct Vector2;
class Component;
class Script;

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
        // this is intended, each object should only have one of any component, 
        // and the other functions are built on this assumption
        mComponents[typeid(ComponentType)] = std::make_unique<ComponentType>(std::forward<Args>(args));
    }

    // -- script functions --
    template <typename ScriptType>
    ScriptType* GetScript()
    {
        if (HasScript<ScriptType>()){
            return static_cast<ScriptType*>(mScripts.at(typeid(ScriptType)));
        }
        else {
            return nullptr;
        }
    }

    template <typename ScriptType>
    bool HasScript()
    {
        return mScripts.contains(typeid(ScriptType))
    }

    template <typename ScriptType, typename... Args>
    void AddScript(Args&&... args)
    {
        // overwrites the index if there a component there already
        // this is intended, each object should only have one of any script, 
        // and the other functions are built on this assumption
        mScripts[typeid(ScriptType)] = std::make_unique<ScriptType>(std::forward<Args>(args));
    }

    private:
    SDL_FRect mTransform;
    std::unordered_map<std::type_index, std::unique_ptr<Component>> mComponents;
    std::unordered_map<std::type_index, std::unique_ptr<Script>> mScripts; 
};

#endif
