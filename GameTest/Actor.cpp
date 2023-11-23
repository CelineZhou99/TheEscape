#include "stdafx.h"
#include "Actor.h"

void Actor::UpdateActorPosition(float move_by_x, float move_by_y)
{
	UpdatePosition(move_by_x, move_by_y);
	GetRenderer()->MoveSpritePosition(move_by_x, move_by_y);
}

void Actor::UpdateAnimatedActorPosition(float move_by_x, float move_by_y, FacingDirection direction)
{
	UpdatePosition(move_by_x, move_by_y);
	GetRenderer()->SetAnimation(direction);
}

void Actor::UpdatePosition(float move_by_x, float move_by_y)
{
	GetTransform().MoveVectorPosition(move_by_x, move_by_y);
	GetCollider()->MoveColliderPosition(move_by_x, move_by_y);
}
