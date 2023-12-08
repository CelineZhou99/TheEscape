#pragma once
#include "PlayerState.h"
class PlayerStateIdle :
    public PlayerState
{
public:
    PlayerStateIdle(Player* player) : PlayerState(player) {}

    void SetSpriteImage() override;

};

