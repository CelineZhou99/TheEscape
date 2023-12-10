#pragma once
#include "GameObject.h"
#include "../Colliders/BoxCollider.h"

#define PLAYER_MOVE_BY 2
#define MOVABLE_OBJECT_MOVE_BY 64
#define IMAGE_SIZE_HALF 32
#define ANIMATION_SPEED 0.2f

class Actor :
    public GameObject
{
public:
    Actor(std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag) : GameObject(renderer, pos_x, pos_y, tag)
    {
        float top_left_x = pos_x - GetRenderer()->GetSprite()->GetWidth() / 2;
        float top_left_y = pos_y + GetRenderer()->GetSprite()->GetHeight() / 2;
        Vector2D collider_position(top_left_x, top_left_y);

        _collider = std::make_shared<BoxCollider>(collider_position, GetRenderer()->GetSprite()->GetWidth(), GetRenderer()->GetSprite()->GetHeight());
    }

    std::shared_ptr<BoxCollider> GetCollider() { return _collider; }

    void UpdateActorPosition(float& move_by_x, float& move_by_y);
   
private:
    std::shared_ptr<BoxCollider> _collider;
};

