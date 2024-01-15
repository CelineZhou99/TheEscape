#pragma once
#include "IPressurePlateState.h"
#include "../Observers/Goal.h"

class PressurePlateStateOn :
    public IPressurePlateState
{
public:
	PressurePlateStateOn(PressurePlate* pressure_plate) : IPressurePlateState(pressure_plate) {}

	void PlaySFX() override;
	void UpdateGoalProgress(Goal* goal) override;
};

