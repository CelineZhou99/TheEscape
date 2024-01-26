#pragma once
#include "IPressurePlateState.h"

#define PRESSURE_PLATE_ON_SOUND ".\\Data\\Sounds\\SwitchOn.wav"

class Goal;
class PressurePlate;

class PressurePlateStateOn :
    public IPressurePlateState
{
public:
	PressurePlateStateOn(PressurePlate* pressure_plate) : _pressure_plate(pressure_plate) {}

	void PlaySFX() override;
	void UpdateGoalProgress(Goal* goal) override;

private:
	PressurePlate* _pressure_plate;
};

