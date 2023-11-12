#pragma once
#include "Actor.h"
#include "BoxCollider.h"

class Player :
    public Actor
{
public:
    Player(const char* file_name, unsigned int columns, unsigned int rows, float pos_x, float pos_y) : Actor(file_name, columns, rows, pos_x, pos_y)
    {
        Actor::Actor(file_name, columns, rows, pos_x, pos_y);

        float top_left_x = pos_x - GetRenderer()->GetSprite()->GetWidth() / 2;
        float top_left_y = pos_y + GetRenderer()->GetSprite()->GetHeight() / 2;
        Vector2D* collider_position = new Vector2D(top_left_x, top_left_y);

        _collider = new BoxCollider(collider_position, GetRenderer()->GetSprite()->GetWidth(), GetRenderer()->GetSprite()->GetHeight());
    }

    BoxCollider* GetCollider() { return _collider; }

private:
    BoxCollider* _collider; // box collider
};

