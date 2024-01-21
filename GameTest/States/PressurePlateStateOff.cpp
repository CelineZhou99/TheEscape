#include "stdafx.h"
#include "PressurePlateStateOff.h"
#include "../App/app.h"
#include "../Observers/Goal.h"

void PressurePlateStateOff::PlaySFX()
{
	App::PlaySound(PRESSURE_PLATE_OFF_SOUND);
}

void PressurePlateStateOff::UpdateGoalProgress(Goal* goal)
{
	goal->IncrementContextCount();
	goal->NotifySubscribers();
}
