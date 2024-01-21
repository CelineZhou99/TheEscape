#include "stdafx.h"
#include "PressurePlateStateOn.h"
#include "../App/app.h"
#include "../Observers/Goal.h"

void PressurePlateStateOn::PlaySFX()
{
	App::PlaySound(PRESSURE_PLATE_ON_SOUND);
}

void PressurePlateStateOn::UpdateGoalProgress(Goal* goal)
{
	goal->DecrementContextCount();
	goal->NotifySubscribers();
}
