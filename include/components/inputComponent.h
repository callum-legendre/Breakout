#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "component.h"
#include "vector2.h"

struct PlayerInput
{
    Vector2 mousePos = {0,0};
    bool lMouseClick = false;
};

class InputComponent : public Component
{
    public:
    InputComponent(GameObject* parent);

    void SetInput(PlayerInput newInput);
};

#endif
