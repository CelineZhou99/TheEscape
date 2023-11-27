#include "stdafx.h"
#include "Actor.h"

void Actor::UpdateActorPosition(float move_by_x, float move_by_y)
{
	GetTransform().MoveVectorPosition(move_by_x, move_by_y);
	GetRenderer()->MoveSpritePosition(move_by_x, move_by_y);
	GetCollider()->MoveColliderPosition(move_by_x, move_by_y);
}
