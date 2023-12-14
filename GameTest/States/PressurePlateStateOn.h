#pragma once
#include "PressurePlateState.h"
#include "../Observers/Goal.h"

class PressurePlateStateOn :
    public PressurePlateState
{
public:
	PressurePlateStateOn(PressurePlate* pressure_plate) : PressurePlateState(pressure_plate) {}

	void PlaySFX() override;
	void UpdateGoalProgress(Goal* goal) override;
};

