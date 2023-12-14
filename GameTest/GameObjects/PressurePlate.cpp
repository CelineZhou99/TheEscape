#include "stdafx.h"
#include "PressurePlate.h"
#include "../Observers/Goal.h"

void PressurePlate::SetState(PressurePlateStateType state, Goal* goal)
{
	if (_state_type != state)
	{
		_state_type = state;
		PressurePlateStateMap::iterator it = _pressure_plate_state_map.find(_state_type);
		if (it != _pressure_plate_state_map.end())
		{
			std::shared_ptr<PressurePlateState> p_state = it->second;
			p_state->PlaySFX();
			p_state->UpdateGoalProgress(goal);
		}
	}
	
}
