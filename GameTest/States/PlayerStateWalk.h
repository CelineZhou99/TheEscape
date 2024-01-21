#pragma once
#include "IPlayerState.h"

class PlayerStateWalk :
    public IPlayerState
{
public:
    PlayerStateWalk(Player* player) : IPlayerState(player) {}

    void SetSpriteImage() override;
};

