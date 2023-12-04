#pragma once

class Player;

enum PlayerStateType
{
	IDLE,
	WALK
};

class PlayerState
{
	// interface for player states
public:
	PlayerState(Player* player) : _player(player) {}

	virtual void SetSpriteImage() = 0;
	virtual PlayerStateType GetStateType() = 0;

protected:
	Player* _player;
};

