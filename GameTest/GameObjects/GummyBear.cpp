#include "stdafx.h"
#include "GummyBear.h"
#include "../World.h"

void GummyBear::OnInteractWithPlayer(World& world)
{
	world.GetPlayer()->GetInventory()->AddToInventory(this);
	world.GetPlayer()->SetCanShoot(world);
	App::PlaySound(ITEM_COLLECT_SOUND);
	world.GetCurrScene()->RemoveItemFromMap(*_transform, this);
	world.GetCurrScene()->RemoveFromSceneLayers(this, LayerType::FOREGROUND);
}
