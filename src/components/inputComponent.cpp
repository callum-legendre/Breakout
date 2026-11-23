#include "components/inputComponent.h"

#include "script.h"
#include "gameObject.h"

InputComponent::InputComponent(GameObject* parent) : Component(parent) {}

void InputComponent::SetInput(PlayerInput newInput)
{
    mParent->CallScripts(&Script::StoreInput, newInput);
}
