#ifndef SCRIPT_H
#define SCRIPT_H

class GameObject;
class ColliderComponent;

class Script
{
    public:
    Script(GameObject* parent) {mParent = parent;}
    virtual ~Script() = default;
    virtual void OnCollision(ColliderComponent* thisCollider, ColliderComponent* otherCollisder) = default;
    virtual void Update() = default;

    private:
    GameObject* mParent;
};

#endif
