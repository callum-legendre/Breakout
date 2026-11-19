#include "components/inputComponent.h"


InputComponent::InputComponent(GameObject* parent) : Component(parent) {}

void InputComponent::SetInput(PlayerInput newInput)
{
    mInput = newInput;
}

PlayerInput InputComponent::GetInput()
{
    return mInput;
}
