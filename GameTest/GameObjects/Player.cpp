#include "stdafx.h"
#include "Player.h"
#include "../World.h"

void Player::SetState(PlayerStateType state)
{
	if (_state_type != state)
	{
		_state_type = state;
		PlayerStateMap::iterator it = _player_state_map.find(_state_type);
		if (it != _player_state_map.end())
		{
			std::shared_ptr<IPlayerState> p_state = it->second;
			p_state->SetSpriteImage();
		}
	}
}

void Player::TakeDamage()
{
	if (!_is_invulnerable)
	{
		Actor::TakeDamage();
		App::PlaySound(HURT_SOUND);
		if (!GetHealthComponent()->IsDead())
		{
			// after being damaged, player will become invulnerable for a short duration
			_is_invulnerable = true;
		}
	}
}

void Player::SetCanShoot(World& world)
{
	_can_shoot = true;
	world.SetDialogue(&_enable_shoot_dialogue);
}

void Player::Update(float deltaTime, bool player_requested_move, bool player_will_move, FacingDirection direction, float player_move_by_x, float player_move_by_y)
{
	if (_is_invulnerable)
	{
		InvulnerabilityCountdown(deltaTime);
	}

	SetPlayerColour();

	if (player_requested_move)
	{
		SetState(PlayerStateType::WALK);
	}
	else
	{
		SetState(PlayerStateType::IDLE);
	}

	_renderer->SetAnimation(direction);

	if (player_will_move)
	{
		UpdateAnimatedActorPosition(player_move_by_x, player_move_by_y, direction);
	}
}

void Player::InvulnerabilityCountdown(float deltaTime)
{
	start_timer += deltaTime / 1000;
	if (start_timer >= stop_timer)
	{
		start_timer = 0.f;
		_is_invulnerable = false;
	}
}

void Player::SetPlayerColour()
{
	if (_is_invulnerable)
	{
		_renderer->GetSprite()->SetColor(0.66f, 0.66f, 0.66f);
	}
	else
	{
		_renderer->GetSprite()->SetColor(1, 1, 1);
	}
}
