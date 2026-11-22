#include "vector2.h"

Vector2::Vector2(float xPos, float yPos)
{
    x = xPos;
    y = yPos;
}

bool Vector2::operator==(const Vector2& rvalue) const
{
    if (x == rvalue.x && y == rvalue.y){
        return true;
    }
    else {
        return false;
    }
}
