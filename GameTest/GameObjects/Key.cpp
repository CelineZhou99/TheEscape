#include "stdafx.h"
#include "Key.h"
#include "../World.h"

void Key::OnInteractWithPlayer(World& world)
{
	world.player->GetInventory()->AddToInventory(*this);
	world.current_scene->RemoveFromSceneLayers(this, LayerType::FOREGROUND);
}
