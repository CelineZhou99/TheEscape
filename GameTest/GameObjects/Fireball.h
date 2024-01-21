#pragma once
#include "Actor.h"

class GameObject;
class Scene;

class Fireball :
    public Actor
{
public:
    Fireball(std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag, FacingDirection direction) : 
        Actor(renderer, pos_x, pos_y, tag), _direction(direction) {}

    void OnCollideWithObject(GameObject* object, Scene* scene);

    FacingDirection GetFacingDirection() { return _direction; }

private:
    FacingDirection _direction;
};

