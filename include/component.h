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

    GameObject* GetParent()
    {
        return mParent;
    }

    protected:
    GameObject* mParent;
};

#endif
