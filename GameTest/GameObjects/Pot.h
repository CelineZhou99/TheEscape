#pragma once
#include "Actor.h"
#include "HealthComponent.h"
#include "../Scenes/Scene.h"

class Pot :
    public Actor
{
public:
    Pot(unsigned short id, std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag, HealthComponentPtr health_component) : 
        Actor(id, renderer, pos_x, pos_y, tag, health_component) {}
};

