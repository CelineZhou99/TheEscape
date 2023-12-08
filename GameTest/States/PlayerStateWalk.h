#pragma once
#include "PlayerState.h"
class PlayerStateWalk :
    public PlayerState
{
public:
    PlayerStateWalk(Player* player) : PlayerState(player) {}

    void SetSpriteImage() override;

};

