#ifndef VECTOR2_H
#define VECTOR2_H
/* 
barebones vector library that contains only the functions that I need. Will add to this as the need arises
*/

#include <concepts>

template <typename T>
concept Number = std::same_as<T, int> || std::same_as<T, float> || std::same_as<T, double>;

struct Vector2
{
    Vector2(float xPos, float yPos);
    float x;
    float y;

    bool operator==(const Vector2& rvalue) const;

    template <Number T>
    Vector2 operator*(T scalar) const
    {
        return Vector2(x * scalar, y * scalar);
    }
};


#endif
