#pragma once

#include "Actor.h"

class Controller
{
public:
	Controller(std::shared_ptr<Actor> actor) : controlled_actor(actor)
	{
		velocity = 0;
	}

protected:
	std::shared_ptr<Actor> controlled_actor;
	float velocity;
};

