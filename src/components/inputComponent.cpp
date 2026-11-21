#include "components/inputComponent.h"

#include "gameObject.h"

InputComponent::InputComponent(GameObject* parent) : Component(parent) {}

void InputComponent::SetInput(PlayerInput newInput)
{
    mParent->CallScripts(&Script::StoreInput, newInput);
}
