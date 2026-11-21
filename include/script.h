#ifndef SCRIPT_H
#define SCRIPT_H

class GameObject;
class ColliderComponent;
struct PlayerInput

class Script
{
    public:
    Script(GameObject* parent) {mParent = parent;}
    virtual ~Script() = default;
    virtual void OnCollision(ColliderComponent* thisCollider, ColliderComponent* otherCollisder) = default;
    virtual void Update() = default;
    virtual void StoreInput(PlayerInput input) {mInput = input} // was unsure about making this virtual or not, but i figure i may want to override this, so why not

    private:
    GameObject* mParent;
    PlayerInput mInput;
};

#endif
