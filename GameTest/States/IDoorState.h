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
	virtual void SetSpriteImage() = 0;
	virtual void OnCollideWithPlayer(World& world) = 0;
};

