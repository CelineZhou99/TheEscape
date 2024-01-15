#pragma once
#include "IPressurePlateState.h"
#include "../Observers/Goal.h"

class PressurePlateStateOff :
    public IPressurePlateState
{
public:
	PressurePlateStateOff(PressurePlate* pressure_plate) : IPressurePlateState(pressure_plate) {}

	void PlaySFX() override;
	void UpdateGoalProgress(Goal* goal) override;
};

