#include "stdafx.h"
#include "../GameObjects/Door.h"
#include "DoorStateLocked.h"
#include "../World.h"

void DoorStateLocked::SetSpriteImage()
{
	float x, y = 0;
	_door->GetRenderer()->GetSprite()->GetPosition(x, y);
	_door->GetRenderer()->SetSprite(".\\Images\\DungeonDoorLocked.bmp", 1, 1);
	_door->GetRenderer()->GetSprite()->SetPosition(x, y);
}

void DoorStateLocked::OnCollideWithPlayer(World& world)
{
	// if player has key, unlock 
	// if player doesn't have key, stay locked
}
