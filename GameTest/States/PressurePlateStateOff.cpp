#include "stdafx.h"
#include "PressurePlateStateOff.h"
#include "../App/app.h"

void PressurePlateStateOff::PlaySFX()
{
	App::PlaySound(".\\Data\\Sounds\\SwitchOff.wav");
}

void PressurePlateStateOff::UpdateGoalProgress(Goal* goal)
{
	goal->IncrementContextCount();
	goal->NotifySubscribers();
}
