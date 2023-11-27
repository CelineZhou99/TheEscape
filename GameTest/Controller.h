#pragma once

#include "Actor.h"

class Controller
{
public:
	Controller(Actor * actor) : controlled_actor(actor) 
	{
		velocity = 0;
	}

protected:
	Actor* controlled_actor;
	float velocity;
};

