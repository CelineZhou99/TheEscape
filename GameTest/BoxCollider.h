#pragma once
#include "Collider.h"

class BoxCollider :
    public Collider
{
public:
    BoxCollider(Vector2D position, float width, float height) : Collider(position, width, height) {}

    bool CheckCollision(Collider* obj_1_collider, Collider* obj_2_collider) override; // override the pure virtual function
};

