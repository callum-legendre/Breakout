#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

struct SDL_FRect;
struct Vector2;

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

    // templated get and set component functions will go here once componentns are done

    // same as above with scripts

    private:
    SDL_FRect mTransform;
    // unordered map of components
    // unordered map of scripts
};

#endif
