#pragma once
#include "Actor.h"
#include "Enemy.h"

#define BLACKBOARD_MOVE_TO_LOCATION "MoveToLocation"
#define BLACKBOARD_MOVE_TO_DIRECTION "MoveToDirection"
#define BLACKBOARD_PLAYER "Player"

class Player;
class Scene;
enum LayerType : uint8_t;

class Slime :
    public Actor, public Enemy
{
public:
    Slime(unsigned short id, std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag, HealthComponentPtr health_component, Player* player, Scene* scene) : 
        Actor(id, renderer, pos_x, pos_y, tag, health_component), _danger_range(2)
    {
        SetSpeed(0.5f);
        BehaviourTreeInit(scene);
    }

    void BehaviourTreeInit(Scene* scene) override;

    BehaviourNodeState MoveTo(Scene* scene) override;
    BehaviourNodeState ChangeColour() override;
    BehaviourNodeState SetMoveToLocation(Scene* scene) override;

    int GetAggroRange() const { return _danger_range; }

    void OnDeath(Scene* scene, LayerType layer);

    void Update(float deltaTime, Scene* scene);

private:
    int _danger_range;
};

