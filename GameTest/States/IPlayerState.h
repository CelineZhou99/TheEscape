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
	virtual void SetSpriteImage() = 0;
};

