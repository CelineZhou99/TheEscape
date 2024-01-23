#pragma once
#include "Actor.h"

#define IMPACT_ENEMY_SOUND ".\\Data\\Sounds\\FireHitEnemy.wav"
#define IMPACT_DESTRUCTABLE_SOUND ".\\Data\\Sounds\\Shatter.wav"
#define IMPACT_OBJECT_SOUND ".\\Data\\Sounds\\FireHit.wav"

class GameObject;
class Scene;

class Fireball :
    public Actor
{
public:
    Fireball(unsigned short id, std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag, FacingDirection direction) :
        Actor(id, renderer, pos_x, pos_y, tag), _direction(direction) {}

    void OnCollideWithObject(GameObject* object, Scene* scene);

    FacingDirection GetFacingDirection() { return _direction; }

    float GetSpeed() { return 5.f; }

private:
    FacingDirection _direction;
};

