#pragma once
#include "Actor.h"
#include "BoxCollider.h"

class SquareActor :
    public Actor
{
public:
    SquareActor(const char* file_name, unsigned int columns, unsigned int rows, float pos_x, float pos_y, TagType tag) : Actor(file_name, columns, rows, pos_x, pos_y, tag)
    {
        float top_left_x = pos_x - GetRenderer().GetSprite()->GetWidth() / 2;
        float top_left_y = pos_y + GetRenderer().GetSprite()->GetHeight() / 2;
        Vector2D collider_position(top_left_x, top_left_y);

        _collider = new BoxCollider(collider_position, GetRenderer().GetSprite()->GetWidth(), GetRenderer().GetSprite()->GetHeight());
    }

    BoxCollider* GetCollider() { return _collider; }
    void CleanUp() { delete _collider; }

private:
    BoxCollider* _collider; // box collider
};

