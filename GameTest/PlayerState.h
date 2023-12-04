#pragma once

class Player;

class PlayerState
{
	// interface for player states
public:
	PlayerState(Player* player) : _player(player) {}

	virtual void SetSpriteImage() = 0;

protected:
	Player* _player;
};

