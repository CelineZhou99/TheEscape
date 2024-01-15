#pragma once
#include "IPlayerState.h"
class PlayerStateIdle :
    public IPlayerState
{
public:
    PlayerStateIdle(Player* player) : IPlayerState(player) {}

    void SetSpriteImage() override;

};

