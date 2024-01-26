#include "stdafx.h"
#include "Key.h"
#include "../World.h"
#include <unordered_map>

void Key::OnInteractWithPlayer(World& world)
{
	App::PlaySound(ITEM_COLLECT_SOUND);

	world.GetPlayer()->GetInventory()->AddToInventory(this);
	world.GetCurrScene()->RemoveItemFromMap(*_transform, this);
	world.GetCurrScene()->RemoveFromSceneLayers(this, LayerType::FOREGROUND);

	// remove from spawned rewards
	SpawnedRewardsMap::iterator it;
	for (it = world.GetSpawnedRewards().begin(); it != world.GetSpawnedRewards().end(); ++it)
	{
		if (it->second->GetItemType() == GetItemType() &&
			it->second->GetTransform()->X() == _transform->X() &&
			it->second->GetTransform()->Y() == _transform->Y())
		{
			world.GetSpawnedRewards().erase(it);
			break;
		}
	}
}
