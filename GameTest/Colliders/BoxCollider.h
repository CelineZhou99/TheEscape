#pragma once
#include "ColliderBase.h"

class BoxCollider :
    public ColliderBase
{
public:
    BoxCollider(Vector2D position, float width, float height) : ColliderBase(position, width, height) {}

    bool CheckCollision(ColliderBase& obj_1_collider, ColliderBase& obj_2_collider) override;
};

