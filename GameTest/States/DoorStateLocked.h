#pragma once
#include "IDoorState.h"
#include <vector>

#define DOOR_OPEN_SOUND ".\\Data\\Sounds\\DoorOpen.wav"

using dialogue = std::vector<const char*>;

class DoorStateLocked :
    public IDoorState
{
public:
    DoorStateLocked(Door* door) : IDoorState(door)
    {
        dialogue no_key = { "This door seems locked.", "There must be a way to open it."};
        dialogue wrong_key = { "*Inserts key*", "This key doesn't seem to fit the lock..." };
        dialogue right_key = { "*Inserts key*", "The door opened." };
        _dialogue_locked_no_key = std::make_shared<dialogue>(no_key);
        _dialogue_locked_wrong_key = std::make_shared<dialogue>(wrong_key);
        _dialogue_locked_right_key = std::make_shared<dialogue>(right_key);
    }

    void SetSpriteImage() override;
    void OnCollideWithPlayer(World& world) override;

private:
    std::shared_ptr<dialogue> _dialogue_locked_no_key;
    std::shared_ptr<dialogue> _dialogue_locked_wrong_key;
    std::shared_ptr<dialogue> _dialogue_locked_right_key;
};

