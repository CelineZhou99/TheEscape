#include "stdafx.h"
#include "PressurePlateStateOn.h"

void PressurePlateStateOn::PlayVFX()
{
	// TODO: play sound
}

void PressurePlateStateOn::UpdateGoalProgress(Goal* goal)
{
	goal->DecrementContextCount();
	goal->NotifySubscribers();
}
