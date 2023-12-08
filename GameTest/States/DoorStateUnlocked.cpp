#include "stdafx.h"
#include "../GameObjects/Door.h"
#include "DoorStateUnlocked.h"

void DoorStateUnlocked::SetSpriteImage()
{
	float x, y = 0;
	_door->GetRenderer()->GetSprite()->GetPosition(x, y);
	_door->GetRenderer()->SetSprite(".\\Images\\DungeonDoorUnlocked.bmp", 1, 1);
	_door->GetRenderer()->GetSprite()->SetPosition(x, y);
}

void DoorStateUnlocked::OnCollideWithPlayer()
{
	// let player through
	
}
