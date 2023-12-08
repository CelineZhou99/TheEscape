#include "stdafx.h"
#include "Player.h"

void Player::SetState(PlayerStateType state)
{
	if (_state_type != state)
	{
		_state_type = state;
		_player_state_map.find(_state_type)->second->SetSpriteImage();
	}
}
