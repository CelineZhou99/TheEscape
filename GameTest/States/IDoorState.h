#pragma once

class Door;
class World;

enum DoorStateType : uint8_t
{
	LOCKED,
	UNLOCKED
};

class IDoorState
{
public:
	IDoorState(Door* door) : _door(door) {}

	virtual void SetSpriteImage() = 0;
	virtual void OnCollideWithPlayer(World& world) = 0;

protected:
	Door* _door;
};

