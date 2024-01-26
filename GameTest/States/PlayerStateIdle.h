#pragma once
#include "IPlayerState.h"

class Player;

class PlayerStateIdle :
    public IPlayerState
{
public:
    PlayerStateIdle(Player* player) : _player(player) {}

    void SetSpriteImage() override;

private:
    Player* _player;
};

