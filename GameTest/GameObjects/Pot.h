#pragma once
#include "Actor.h"
#include "IHealthSystem.h"

class Pot :
    public Actor, public IHealthSystem
{
public:
    Pot(std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag) : Actor(renderer, pos_x, pos_y, tag)
    {
        SetMaxHealth(1);
    }

    void TakeDamage() override { --_curr_health; }
};

