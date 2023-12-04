#include "stdafx.h"
#include "Player.h"

void Player::SetState(std::shared_ptr<PlayerState> state)
{
	_player_state = state;
	_player_state->SetSpriteImage();
}
