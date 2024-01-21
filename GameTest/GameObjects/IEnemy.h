#pragma once
#include "../BehaviourTree/BehaviourTree.h"
#include "IHealthSystem.h"

class Scene;

using bt_ptr = std::shared_ptr<BehaviourTree>;

class IEnemy : public IHealthSystem
{
public:
	bt_ptr GetBehaviourTree() { return _behaviour_tree; }
	virtual void BehaviourTreeInit(Scene* scene) = 0;

	virtual BehaviourNodeState MoveTo(Scene* scene) = 0;
	virtual BehaviourNodeState SetMoveToLocation(Scene* scene) = 0;

	void TakeDamage() override;

protected:
	bt_ptr _behaviour_tree = nullptr;
};

