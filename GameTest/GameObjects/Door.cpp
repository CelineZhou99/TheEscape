#include "stdafx.h"
#include "Door.h"
#include "../World.h"

void Door::SetState(DoorStateType state)
{
	if (_state_type != state)
	{
		_state_type = state;
		DoorStateMap::iterator it = _door_state_map.find(_state_type);
		if (it != _door_state_map.end())
		{
			std::shared_ptr<DoorState> d_state = it->second;
			d_state->SetSpriteImage();
		}
	}
	
}

void Door::OnPlayerCollision(World& world)
{
	DoorStateMap::iterator it = _door_state_map.find(_state_type);
	if (it != _door_state_map.end())
	{
		std::shared_ptr<DoorState> d_state = it->second;
		d_state->OnCollideWithPlayer(world);
	}
}
