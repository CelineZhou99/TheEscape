#pragma once
#include "DoorState.h"
class DoorStateUnlocked :
    public DoorState
{
public:
    DoorStateUnlocked(Door* door) : DoorState(door) {}

    void SetSpriteImage() override;
    void OnCollideWithPlayer(World& world) override;
};

