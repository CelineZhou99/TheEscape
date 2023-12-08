#pragma once

class PressurePlate;
class Goal;

enum PressurePlateStateType
{
	ON,
	OFF
};

class PressurePlateState
{
	// interface for pressure plate states
public:
	PressurePlateState(PressurePlate* pressure_plate) : _pressure_plate(pressure_plate) {}

	virtual void PlayVFX() = 0;
	virtual void UpdateGoalProgress(Goal* goal) = 0;

protected:
	PressurePlate* _pressure_plate;
};

