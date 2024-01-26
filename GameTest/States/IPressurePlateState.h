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
	virtual void PlaySFX() = 0;
	virtual void UpdateGoalProgress(Goal* goal) = 0;
};

