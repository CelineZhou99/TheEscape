#include "stdafx.h"
#include "Player.h"

void Player::SetState(PlayerStateType state)
{
	if (_state_type != state)
	{
		_state_type = state;
		PlayerStateMap::iterator it = _player_state_map.find(_state_type);
		if (it != _player_state_map.end())
		{
			std::shared_ptr<PlayerState> p_state = it->second;
			p_state->SetSpriteImage();
		}
	}
}
