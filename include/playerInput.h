#ifndef PLAYERINPUT_H
#define PLAYERINPUT_H

#include "vector2.h"

struct PlayerInput
{
    Vector2 mousePos = {0,0};
    bool lMouseClick = false;
};

#endif
