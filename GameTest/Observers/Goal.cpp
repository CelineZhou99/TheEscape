#include "stdafx.h"
#include "Goal.h"
#include "../Scenes/Scene.h"
#include "../GameObjects/GameObject.h"

bool Goal::IsGoalComplete()
{
	if (_goal_context_count <= 0)
	{
		return true;
	}
	return false;
}

void Goal::IncrementContextCount()
{
	++_goal_context_count;
}

void Goal::DecrementContextCount()
{
	--_goal_context_count;
}

void Goal::SpawnReward(Scene* scene)
{
	// TODO: FIX INCREMENTING FIRST THEN DECREMENTING BUG WILL SPAWN REWARD EVEN WHEN ITS NOT FINISHED
	if (_goal_reward == GOAL_REWARD_KEY)
	{
		scene->MakeKey(_goal_reward_tile->GetTransform()->X(), _goal_reward_tile->GetTransform()->Y());
	}
	else if (_goal_reward == GOAL_REWARD_KEY_ESCAPE)
	{
		scene->MakeKeyEscape(_goal_reward_tile->GetTransform()->X(), _goal_reward_tile->GetTransform()->Y());
	}
}
