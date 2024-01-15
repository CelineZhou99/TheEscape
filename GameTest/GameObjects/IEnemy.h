#pragma once
#include "../BehaviourTree/BehaviourTree.h"
#include "Vector2D.h"

class Player;
class Scene;

using bt_ptr = std::shared_ptr<BehaviourTree>;

class IEnemy
{
public:
	bt_ptr GetBehaviourTree() { return _behaviour_tree; }
	virtual void BehaviourTreeInit() = 0;

	virtual BehaviourNodeState MoveTo(Vector2D location) = 0;
	virtual BehaviourNodeState MoveTo(Player* player) = 0;

	void SetRandomLocationWithinDistance(Scene* scene, float distance);

protected:
	bt_ptr _behaviour_tree = nullptr;
	Vector2D _move_to_location = Vector2D();
};

