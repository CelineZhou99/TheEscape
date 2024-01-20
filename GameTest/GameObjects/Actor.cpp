#include "stdafx.h"
#include "Actor.h"

void Actor::UpdateActorPosition(float move_by_x, float move_by_y)
{
	GetTransform()->MoveVectorPosition(move_by_x, move_by_y);
	GetRenderer()->MoveSpritePosition(move_by_x, move_by_y);
	GetCollider()->MoveColliderPosition(move_by_x, move_by_y);
}

void Actor::SetActorPosition(float x, float y, FacingDirection direction)
{
	_transform->SetVectorPosition(x, y);
	_renderer->SetSpritePosition(x, y, direction);
	float top_left_x = x - _renderer->GetSprite()->GetWidth() / 2;
	float top_left_y = y + _renderer->GetSprite()->GetHeight() / 2;
	_collider->SetColliderPosition(top_left_x, top_left_y);
}
