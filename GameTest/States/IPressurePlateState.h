#pragma once

class PressurePlate;
class Goal;

enum PressurePlateStateType : uint8_t
{
	ON,
	OFF
};

class IPressurePlateState
{
	// interface for pressure plate states
public:
	IPressurePlateState(PressurePlate* pressure_plate) : _pressure_plate(pressure_plate) {}

	virtual void PlaySFX() = 0;
	virtual void UpdateGoalProgress(Goal* goal) = 0;

protected:
	PressurePlate* _pressure_plate;
};

