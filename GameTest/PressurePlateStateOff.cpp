#include "stdafx.h"
#include "PressurePlateStateOff.h"

void PressurePlateStateOff::PlayVFX()
{
	// TODO: play sound
}

void PressurePlateStateOff::UpdateGoalProgress(Goal* goal)
{
	goal->IncrementContextCount();
	goal->NotifySubscribers();
}
