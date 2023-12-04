#pragma once

#include "Actor.h"

class Controller
{
public:
	Controller(Actor* actor) : controlled_actor(actor)
	{
		//velocity = Vector2D();
	}

protected:
	Actor* controlled_actor;

	// make this speed and direction
	//Vector2D velocity;
};

