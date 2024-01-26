#pragma once
#include "IDoorState.h"

class Door;

class DoorStateUnlocked :
    public IDoorState
{
public:
    DoorStateUnlocked(Door* door) : _door(door) {}

    void SetSpriteImage() override;
    void OnCollideWithPlayer(World& world) override;

private:
    Door* _door;
};

