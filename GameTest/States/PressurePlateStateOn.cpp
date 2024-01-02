#include "stdafx.h"
#include "PressurePlateStateOn.h"
#include "../App/app.h"

void PressurePlateStateOn::PlaySFX()
{
	// TODO: play sound
	App::PlaySound(".\\Data\\Sounds\\SwitchOn.wav");
}

void PressurePlateStateOn::UpdateGoalProgress(Goal* goal)
{
	goal->DecrementContextCount();
	goal->NotifySubscribers();
}
