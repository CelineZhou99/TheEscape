#pragma once
#include "IPressurePlateState.h"

#define PRESSURE_PLATE_OFF_SOUND ".\\Data\\Sounds\\SwitchOff.wav"

class Goal;
class PressurePlate;

class PressurePlateStateOff :
    public IPressurePlateState
{
public:
	PressurePlateStateOff(PressurePlate* pressure_plate) : _pressure_plate(pressure_plate) {}

	void PlaySFX() override;
	void UpdateGoalProgress(Goal* goal) override;

private:
	PressurePlate* _pressure_plate;
};

