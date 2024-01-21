#include "stdafx.h"
#include "GummyBear.h"
#include "../World.h"

void GummyBear::OnInteractWithPlayer(World& world)
{
	world.player->GetInventory()->AddToInventory(this);
	world.player->SetCanShoot(world);
	App::PlaySound(ITEM_COLLECT_SOUND);
	world.current_scene->RemoveFromSceneLayers(this, LayerType::FOREGROUND);
}
