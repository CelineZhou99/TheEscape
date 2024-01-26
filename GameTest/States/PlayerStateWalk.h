#pragma once
#include "IPlayerState.h"

class Player;

class PlayerStateWalk :
    public IPlayerState
{
public:
    PlayerStateWalk(Player* player) : _player(player) {}

    void SetSpriteImage() override;

private:
    Player* _player;
};

