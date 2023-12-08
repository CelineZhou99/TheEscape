#pragma once
#include "PressurePlateState.h"
#include "Goal.h"

class PressurePlateStateOff :
    public PressurePlateState
{
public:
	PressurePlateStateOff(PressurePlate* pressure_plate) : PressurePlateState(pressure_plate) {}

	void PlayVFX() override;
	void UpdateGoalProgress(Goal* goal) override;
};

