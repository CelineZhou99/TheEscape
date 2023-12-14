#include "stdafx.h"
#include "PressurePlateStateOn.h"

void PressurePlateStateOn::PlaySFX()
{
	// TODO: play sound
}

void PressurePlateStateOn::UpdateGoalProgress(Goal* goal)
{
	goal->DecrementContextCount();
	goal->NotifySubscribers();
}
