#include "stdafx.h"
#include "../GameObjects/Door.h"
#include "DoorStateLocked.h"
#include "../World.h"
#include "../GameObjects/DungeonDoor.h"

void DoorStateLocked::SetSpriteImage()
{
	float x, y = 0;
	_door->GetRenderer()->GetSprite()->GetPosition(x, y);
	_door->GetRenderer()->SetSprite(".\\Data\\Images\\DungeonDoorLocked.bmp", 1, 1);
	_door->GetRenderer()->GetSprite()->SetPosition(x, y);
}

void DoorStateLocked::OnCollideWithPlayer(World& world)
{
	// if player has key, unlock 
	// if player doesn't have key, stay locked
	DungeonDoor& dungeon_door = static_cast<DungeonDoor&>(*_door);
	ItemType required_key_type = dungeon_door.GetRequiredKeyType();
	if (Item* item = world.player->GetInventory()->FindInInventory(required_key_type))
	{
		world.player->GetInventory()->RemoveFromInventory(item);
		_door->SetState(DoorStateType::UNLOCKED);
	}
}
