#include "stdafx.h"
#include "DoorStateLocked.h"
#include "../World.h"
#include "../GameObjects/DungeonDoor.h"

void DoorStateLocked::SetSpriteImage()
{
	float x, y = 0;
	_door->GetRenderer()->GetSprite()->GetPosition(x, y);
	_door->GetRenderer()->SetSprite(IMAGE_DUNGEON_DOOR_LOCKED, 1, 1);
	_door->GetRenderer()->GetSprite()->SetPosition(x, y);
}

void DoorStateLocked::OnCollideWithPlayer(World& world)
{
	// if player has key, unlock 
	// if player doesn't have key, stay locked
	DungeonDoor& dungeon_door = static_cast<DungeonDoor&>(*_door);
	ItemType required_key_type = dungeon_door.GetRequiredKeyType();
	Item* item = nullptr;
	if (item = world.player->GetInventory()->FindInInventory(required_key_type))
	{
		world.text_box->SetDialogue(_dialogue_locked_right_key.get());
		App::PlaySound(DOOR_OPEN_SOUND);
		world.player->GetInventory()->RemoveFromInventory(item);
		_door->SetState(DoorStateType::UNLOCKED);
		world.current_goal->AddToUnlockedDoors(_door->GetDoorId());
	}
	else if (item == nullptr)
	{
		ItemType alt_key_type = required_key_type == ItemType::KEY ? ItemType::KEY_ESCAPE : ItemType::KEY;
		if (item = world.player->GetInventory()->FindInInventory(alt_key_type))
		{
			world.text_box->SetDialogue(_dialogue_locked_wrong_key.get());
		}
		else
		{
			world.text_box->SetDialogue(_dialogue_locked_no_key.get());
		}
	}
}
