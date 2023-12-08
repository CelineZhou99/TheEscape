#pragma once
#include "DoorState.h"
class DoorStateLocked :
    public DoorState
{
public:
    DoorStateLocked(Door* door) : DoorState(door) {}

    void SetSpriteImage() override;
    void OnCollideWithPlayer() override;
};

