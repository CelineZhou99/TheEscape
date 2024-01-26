#pragma once
#include "BehaviourNode.h"

class Player;
class Slime;
class Scene;
class Blackboard;

class SetPlayerInRangeService :
    public BehaviourNode
{
public:
    SetPlayerInRangeService(unsigned short id, Player* player, Slime* slime, Scene* scene, Blackboard* blackboard) : 
        BehaviourNode(id), _player(player), _slime(slime), _scene(scene), _blackboard(blackboard) {}

    bool CanHaveChildren() const override { return false; }
    bool CanAttachService() const override { return false; }

    BehaviourNodeState AssessCurrState() override;

private:
    Player* _player;
    Slime* _slime;
    Scene* _scene;
    Blackboard* _blackboard;
};

