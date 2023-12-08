#include "stdafx.h"
#include "Door.h"

void Door::SetState(DoorStateType state)
{
	if (_state_type != state)
	{
		_state_type = state;
		_door_state_map.find(_state_type)->second->SetSpriteImage();
	}
}

void Door::OnPlayerCollision()
{
	_door_state_map.find(_state_type)->second->OnCollideWithPlayer();
}
