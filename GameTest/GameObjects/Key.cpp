#include "stdafx.h"
#include "Key.h"
#include "../World.h"
#include <unordered_map>

void Key::OnInteractWithPlayer(World& world)
{
	App::PlaySound(ITEM_COLLECT_SOUND);

	world.player->GetInventory()->AddToInventory(this);
	world.current_scene->RemoveFromSceneLayers(this, LayerType::FOREGROUND);
	
	// remove from spawned rewards
	SpawnedRewardsMap::iterator it;
	for (it = world.spawned_rewards.begin(); it != world.spawned_rewards.end(); ++it)
	{
		if (it->second->GetItemType() == GetItemType() &&
			it->second->GetTransform()->X() == _transform->X() &&
			it->second->GetTransform()->Y() == _transform->Y())
		{
			world.spawned_rewards.erase(it);
			break;
		}
	}
}
