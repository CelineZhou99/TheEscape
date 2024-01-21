#pragma once
#include "IPressurePlateState.h"

#define PRESSURE_PLATE_ON_SOUND ".\\Data\\Sounds\\SwitchOn.wav"

class Goal;

class PressurePlateStateOn :
    public IPressurePlateState
{
public:
	PressurePlateStateOn(PressurePlate* pressure_plate) : IPressurePlateState(pressure_plate) {}

	void PlaySFX() override;
	void UpdateGoalProgress(Goal* goal) override;
};

