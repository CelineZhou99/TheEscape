#include "stdafx.h"
#include "Actor.h"
#include "Player.h"
#include "../Scenes/Scene.h"

void Actor::UpdateActorPosition(float move_by_x, float move_by_y)
{
	_transform->MoveVectorPosition(move_by_x, move_by_y);
	_renderer->MoveSpritePosition(move_by_x, move_by_y);
	_collider->MoveColliderPosition(move_by_x, move_by_y);
}

void Actor::UpdateAnimatedActorPosition(float move_by_x, float move_by_y, FacingDirection direction)
{
	_transform->MoveVectorPosition(move_by_x, move_by_y);
	_renderer->SetAnimationWithMovement(direction, move_by_x, move_by_y);
	_collider->MoveColliderPosition(move_by_x, move_by_y);
	if (GetTag() == TagType::PLAYER)
	{
		Player& player = static_cast<Player&>(*this);
		player.SetLastFacingDirection(direction);
	}
}

void Actor::SetActorPosition(float x, float y, FacingDirection direction)
{
	_transform->SetVectorPosition(x, y);
	_renderer->SetSpritePosition(x, y, direction);
	float top_left_x = x - _renderer->GetSprite()->GetWidth() / 2;
	float top_left_y = y + _renderer->GetSprite()->GetHeight() / 2;
	_collider->SetColliderPosition(top_left_x, top_left_y);
}

void Actor::TakeDamage()
{
	if (GetHealthComponent())
	{
		_health_component->TakeDamage();
	}
}

void Actor::OnDeath(Scene* scene, LayerType layer)
{
	scene->RemoveFromSceneLayers(this, layer);
}
