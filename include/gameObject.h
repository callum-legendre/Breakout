#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

struct Vector2;
class Component;
class Script;

#include <unordered_map>
#include <typeindex>
#include <memory>
#include <functional>
#include <SDL3/SDL.h>

class GameObject
{
    public:
    GameObject(float xPos, float yPos, float width, float height);
    ~GameObject();

    // -- transform methods --
        // in this game it makes sense for each object to have an inherent position associated with it
        // which is why all of this in the base gameobject and not a transform component.
        // for the ease of scripting, move operations will be done using vectors that are applied to the SDL rectangle
    SDL_FRect GetTransform();
    Vector2 GetPosition();
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
        return mComponents.contains(typeid(ComponentType));
    }

    // overwrites the index if there a component there already
    // this is intended, each object should only have one of any component, 
    // and the other functions are built on this assumption
    template <typename ComponentType, typename... Args>
    void AddComponent(Args&&... args)
    {
        mComponents[typeid(ComponentType)] = std::make_unique<ComponentType>(std::forward<Args>(args)...);
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
        return mScripts.contains(typeid(ScriptType));
    }

    // overwrites the index if there a component there already
    // this is intended, each object should only have one of any script, 
    // and the other functions are built on this assumption
    template <typename ScriptType, typename... Args>
    void AddScript(Args&&... args)
    {
        mScripts[typeid(ScriptType)] = std::make_unique<ScriptType>(std::forward<Args>(args)...);
    }

    // a function to call the specified member function of each script attached to this object
    template <typename Function, typename... Args>
    void CallScripts(Function function, const Args&... args)
    {
        for (const auto& [type, script] : mScripts){
            std::invoke(function, *script, args...);
        }
    }

    private:
    SDL_FRect mTransform;
    std::unordered_map<std::type_index, std::unique_ptr<Component>> mComponents;
    std::unordered_map<std::type_index, std::unique_ptr<Script>> mScripts; 
};

#endif
