#pragma once
#include "PressurePlateState.h"
#include "../Observers/Goal.h"

class PressurePlateStateOff :
    public PressurePlateState
{
public:
	PressurePlateStateOff(PressurePlate* pressure_plate) : PressurePlateState(pressure_plate) {}

	void PlaySFX() override;
	void UpdateGoalProgress(Goal* goal) override;
};

