#pragma once
#include "Door.h"
#include "Key.h"

class DungeonDoor :
    public Door
{
public:
    DungeonDoor(std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag, DoorStateType state, 
        int id, char* linked_map, ItemType required_key_type) : 
        Door(renderer, pos_x, pos_y, tag, state, id, linked_map),
        _required_key_type(required_key_type) {}

    ItemType GetRequiredKeyType() { return _required_key_type; }

private:
    ItemType _required_key_type;
};

