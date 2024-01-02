#include "stdafx.h"
#include "PressurePlateStateOff.h"
#include "../App/app.h"

void PressurePlateStateOff::PlaySFX()
{
	// TODO: play sound doesn't work as long as its not the test.wav - ask about this
	App::PlaySound(".\\Data\\Sounds\\SoundOff.wav");
}

void PressurePlateStateOff::UpdateGoalProgress(Goal* goal)
{
	goal->IncrementContextCount();
	goal->NotifySubscribers();
}
