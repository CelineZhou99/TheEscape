#include "stdafx.h"
#include "PressurePlateStateOff.h"

void PressurePlateStateOff::PlaySFX()
{
	// TODO: play sound
}

void PressurePlateStateOff::UpdateGoalProgress(Goal* goal)
{
	goal->IncrementContextCount();
	goal->NotifySubscribers();
}
