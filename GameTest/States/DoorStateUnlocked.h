#pragma once
#include "IDoorState.h"

class DoorStateUnlocked :
    public IDoorState
{
public:
    DoorStateUnlocked(Door* door) : IDoorState(door) {}

    void SetSpriteImage() override;
    void OnCollideWithPlayer(World& world) override;
};

