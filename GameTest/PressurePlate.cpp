#include "stdafx.h"
#include "PressurePlate.h"
#include "Goal.h"

void PressurePlate::SetState(PressurePlateStateType state, Goal* goal)
{
	if (_state_type != state)
	{
		_state_type = state;
		_pressure_plate_state_map.find(_state_type)->second->PlayVFX();
		_pressure_plate_state_map.find(_state_type)->second->UpdateGoalProgress(goal);
	}
}
