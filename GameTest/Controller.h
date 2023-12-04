#pragma once

#include "Actor.h"

class Controller
{
public:
	Controller(Actor* actor) : _controlled_actor(actor), _speed(0) {}

	void SetSpeed(float speed) { _speed = speed; }
	bool IsMoving();

protected:
	Actor* _controlled_actor;

	// this is speed for now, but will make it velocity (speed and direction) in the future
	float _speed;
};

