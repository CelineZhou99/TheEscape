#pragma once

#include "../GameObjects/Actor.h"

class Controller
{
public:
	Controller(Actor* actor) : _controlled_actor(actor) {}

	virtual void UpdateControlledActorPosition(float move_by_x, float move_by_y, FacingDirection direction) = 0;
	virtual void SetControlledActorPosition(float x, float y, FacingDirection direction) = 0;

protected:
	Actor* _controlled_actor;
};

