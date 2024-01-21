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
		--_curr_health;
		if (!IsDead())
		{
			// after being damaged, player will become invulnerable for a short duration
			_is_invulnerable = true;
		}
	}
}

void Player::SetCanShoot(World& world)
{
	_can_shoot = true;
	world.text_box->SetDialogue(&_enable_shoot_dialogue);
}
