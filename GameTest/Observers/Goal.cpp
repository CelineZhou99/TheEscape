#include "stdafx.h"
#include "Goal.h"
#include "../Scenes/Scene.h"
#include "../World.h"
#include "../GameObjects/Item.h"

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

void Goal::SpawnReward(Scene* scene, const char* map_file_name)
{
	App::PlaySound(GOAL_COMPLETE_SOUND);

	std::shared_ptr<Item> item = nullptr;
	if (_goal_reward == GOAL_REWARD_KEY)
	{
		item = scene->MakeKey(_goal_reward_tile->GetTransform()->X(), _goal_reward_tile->GetTransform()->Y());
	}
	else if (_goal_reward == GOAL_REWARD_KEY_ESCAPE)
	{
		item = scene->MakeKeyEscape(_goal_reward_tile->GetTransform()->X(), _goal_reward_tile->GetTransform()->Y());
	}
	_world.spawned_rewards[map_file_name] = item;
}

void Goal::AddToUnlockedDoors(unsigned short id)
{
	if (!FindInUnlockedDoors(id))
	{
		_world._unlocked_doors.push_back(id);
	}
}

bool Goal::FindInUnlockedDoors(unsigned short id)
{
	return std::find(_world._unlocked_doors.begin(), _world._unlocked_doors.end(), id) != _world._unlocked_doors.end();
}

std::shared_ptr<Item> Goal::FindInSpawnedRewards(const char* file_name)
{
	if (_world.spawned_rewards.find(file_name) != _world.spawned_rewards.end())
	{
		return _world.spawned_rewards[file_name];
	}
	return nullptr;
}
