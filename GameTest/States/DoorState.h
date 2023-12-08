#pragma once

class Door;

enum DoorStateType
{
	LOCKED,
	UNLOCKED
};

class DoorState
{
public:
	DoorState(Door* door) : _door(door) {}

	virtual void SetSpriteImage() = 0;
	virtual void OnCollideWithPlayer() = 0;

protected:
	Door* _door;
};

