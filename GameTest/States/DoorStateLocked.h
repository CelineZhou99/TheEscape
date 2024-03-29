#pragma once
#include "IDoorState.h"
#include <vector>

#define DOOR_OPEN_SOUND ".\\Data\\Sounds\\DoorOpen.wav"

class Door;

using Dialogue = std::vector<std::string>;

class DoorStateLocked :
    public IDoorState
{
public:
    DoorStateLocked(Door* door) : _door(door)
    {
        Dialogue no_key = { "This door seems locked.", "There must be a way to open it."};
        Dialogue wrong_key = { "*Inserts key*", "This key doesn't seem to fit the lock..." };
        Dialogue right_key = { "*Inserts key*", "The door opened." };
        _dialogue_locked_no_key = std::make_shared<Dialogue>(no_key);
        _dialogue_locked_wrong_key = std::make_shared<Dialogue>(wrong_key);
        _dialogue_locked_right_key = std::make_shared<Dialogue>(right_key);
    }

    void SetSpriteImage() override;
    void OnCollideWithPlayer(World& world) override;

private:
    Door* _door;
    std::shared_ptr<Dialogue> _dialogue_locked_no_key;
    std::shared_ptr<Dialogue> _dialogue_locked_wrong_key;
    std::shared_ptr<Dialogue> _dialogue_locked_right_key;
};

