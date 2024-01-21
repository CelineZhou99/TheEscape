#pragma once
#include "ICollider.h"

class BoxCollider :
    public ICollider
{
public:
    BoxCollider(Vector2D position, float width, float height) : ICollider(position, width, height) {}

    bool CheckCollision(ICollider& obj_1_collider, ICollider& obj_2_collider) override;
};

