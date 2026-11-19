#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component
{
    public:
    Component(GameObject* parent)
    {
        mParent = parent;
    }

    virtual ~Component() = default;

    private:
    GameObject* mParent;
};

#endif
