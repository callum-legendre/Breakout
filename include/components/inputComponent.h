#ifndef INPUTCOMPONENT_H
#define INPUTCOMPONENT_H

#include "component.h"
#include "vector2.h"
#include "playerInput.h"

class InputComponent : public Component
{
    public:
    InputComponent(GameObject* parent);

    void SetInput(PlayerInput newInput);
};

#endif
