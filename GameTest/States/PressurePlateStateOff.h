#pragma once
#include "IPressurePlateState.h"

#define PRESSURE_PLATE_OFF_SOUND ".\\Data\\Sounds\\SwitchOff.wav"

class Goal;

class PressurePlateStateOff :
    public IPressurePlateState
{
public:
	PressurePlateStateOff(PressurePlate* pressure_plate) : IPressurePlateState(pressure_plate) {}

	void PlaySFX() override;
	void UpdateGoalProgress(Goal* goal) override;
};

