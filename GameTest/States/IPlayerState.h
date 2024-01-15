#pragma once

class Player;

enum PlayerStateType : uint8_t
{
	IDLE,
	WALK
};

class IPlayerState
{
	// interface for player states
public:
	IPlayerState(Player* player) : _player(player) {}

	virtual void SetSpriteImage() = 0;

protected:
	Player* _player;
};

