#pragma once
#include "../BehaviourTree/BehaviourTree.h"

class Scene;

using bt_ptr = std::shared_ptr<BehaviourTree>;

class Enemy 
{
public:
	bt_ptr GetBehaviourTree() const { return _behaviour_tree; }
	virtual void BehaviourTreeInit(Scene* scene) = 0;

	virtual BehaviourNodeState MoveTo(Scene* scene) = 0;
	virtual BehaviourNodeState ChangeColour() = 0;
	virtual BehaviourNodeState SetMoveToLocation(Scene* scene) = 0;

protected:
	bt_ptr _behaviour_tree = nullptr;
};

