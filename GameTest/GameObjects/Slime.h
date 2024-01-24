#pragma once
#include "Actor.h"
#include "IEnemy.h"

#define MOVE_TO_LOCATION "MoveToLocation"
#define MOVE_TO_DIRECTION "MoveToDirection"
#define TEMP "Temp"

class Player;
class Scene;

class Slime :
    public Actor, public IEnemy
{
public:
    Slime(unsigned short id, std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag, Player* player, Scene* scene) : 
        Actor(id, renderer, pos_x, pos_y, tag)
    {
        SetMaxHealth(3);
        BehaviourTreeInit(scene);
    }

    void BehaviourTreeInit(Scene* scene) override;

    BehaviourNodeState MoveTo(Scene* scene) override;
    BehaviourNodeState SetMoveToLocation(Scene* scene) override;

    float GetSpeed() { return 0.5f; }

    // temp
    void UpdatePosition(float move_by_x, float move_by_y, FacingDirection direction);

    void OnDeath(Scene* scene) override;
};

