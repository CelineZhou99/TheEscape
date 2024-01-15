#pragma once
#include "Actor.h"
#include "IEnemy.h"

class Slime :
    public Actor, public IEnemy
{
public:
    Slime(std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag) : Actor(renderer, pos_x, pos_y, tag) 
    {
        BehaviourTreeInit();
    }
    void BehaviourTreeInit() override;

    BehaviourNodeState MoveTo(Vector2D location) override;
    BehaviourNodeState MoveTo(Player* player) override;

    BehaviourNodeState SayHello();
    BehaviourNodeState SayBye();
};

