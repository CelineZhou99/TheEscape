#pragma once
#include "Actor.h"
#include "IHealthSystem.h"
#include "../Scenes/Scene.h"

class Pot :
    public Actor, public IHealthSystem
{
public:
    Pot(unsigned short id, std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag) : 
        Actor(id, renderer, pos_x, pos_y, tag)
    {
        SetMaxHealth(1);
    }

    void TakeDamage() override { --_curr_health; }

    void OnDeath(Scene* scene) override { scene->RemoveFromSceneLayers(this, LayerType::FOREGROUND); }
};

