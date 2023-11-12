#pragma once
#include "Collider.h"

class BoxCollider :
    public Collider
{
public:
    BoxCollider(Vector2D* position, float width, float height) : Collider(position, width, height)
    {
        _position = position;
        _collider_width = width;
        _collider_height = height;
    }

    bool CheckCollision(Collider* obj_1_collider, Collider* obj_2_collider); // override the pure virtual function
private:
    Vector2D* _position; // top-left corner
    float _collider_width;
    float _collider_height;
};

