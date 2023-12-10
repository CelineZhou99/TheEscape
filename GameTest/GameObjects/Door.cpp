#include "stdafx.h"
#include "Door.h"
#include "../World.h"

void Door::SetState(DoorStateType state)
{
	if (_state_type != state)
	{
		_state_type = state;
		_door_state_map.find(_state_type)->second->SetSpriteImage();
	}
}

void Door::OnPlayerCollision(World& world)
{
	_door_state_map.find(_state_type)->second->OnCollideWithPlayer(world);
}
