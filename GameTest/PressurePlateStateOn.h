#pragma once
#include "PressurePlateState.h"
#include "Goal.h"

class PressurePlateStateOn :
    public PressurePlateState
{
public:
	PressurePlateStateOn(PressurePlate* pressure_plate) : PressurePlateState(pressure_plate) {}

	void PlayVFX() override;
	void UpdateGoalProgress(Goal* goal) override;
};

