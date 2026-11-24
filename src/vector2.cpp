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

float Dot(Vector2 vec1, Vector2 vec2)
{
    return (vec1.x * vec2.x) + (vec1.y * vec2.y);
}

Vector2 Distance(Vector2 vec1, Vector2 vec2)
{
    return Vector2(vec1.x - vec2.x, vec1.y - vec2.y);
}
