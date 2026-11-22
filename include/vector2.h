#ifndef VECTOR2_H
#define VECTOR2_H
/* 
barebones vector library that contains only the functions that I need. Will add to this as the need arises
*/

struct Vector2
{
    Vector2(float xPos, float yPos);
    float x;
    float y;

    bool operator==(const Vector2& rvalue) const;
};


#endif
