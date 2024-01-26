#pragma once
#include "GameObject.h"
#include "../Colliders/BoxCollider.h"
#include "HealthComponent.h"

#define PLAYER_MOVE_BY 2
#define MOVABLE_OBJECT_MOVE_BY 64
#define TILE_SIZE_HALF 32
#define TILE_SIZE_FULL 64
#define ANIMATION_SPEED 0.2f

class Scene;
enum LayerType : uint8_t;

using HealthComponentPtr = std::shared_ptr<HealthComponent>;

class Actor :
    public GameObject
{
public:
    Actor(unsigned short id, std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag, HealthComponentPtr health_component = nullptr) :
        GameObject(id, renderer, pos_x, pos_y, tag)
    {
        float top_left_x = pos_x - GetRenderer()->GetSprite()->GetWidth() / 2;
        float top_left_y = pos_y + GetRenderer()->GetSprite()->GetHeight() / 2;
        Vector2D position = Vector2D(top_left_x, top_left_y);

        _collider = std::make_shared<BoxCollider>(position, GetRenderer()->GetSprite()->GetWidth(), GetRenderer()->GetSprite()->GetHeight());
        _health_component = health_component;
        _speed = 0;
    }

    std::shared_ptr<BoxCollider> GetCollider() const { return _collider; }

    void UpdateActorPosition(float move_by_x, float move_by_y);
    void UpdateAnimatedActorPosition(float move_by_x, float move_by_y, FacingDirection direction);

    // default facing direction on actor to be down
    void SetActorPosition(float x, float y, FacingDirection direction = FacingDirection::DOWN);

    HealthComponentPtr GetHealthComponent() const { return _health_component; }

    void TakeDamage();

    float GetSpeed() const { return _speed; }
    void SetSpeed(float speed) { _speed = speed; }

    void OnDeath(Scene* scene, LayerType layer);

protected:
    std::shared_ptr<BoxCollider> _collider;
    HealthComponentPtr _health_component;
    float _speed;
};

