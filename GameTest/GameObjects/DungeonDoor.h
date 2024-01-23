#pragma once
#include "Door.h"
#include "../GameObjects/Item.h"

class DungeonDoor :
    public Door
{
public:
    DungeonDoor(unsigned short id, std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag, DoorStateType state,
        unsigned short _door_id, char* linked_map, ItemType required_key_type) : 
        Door(id, renderer, pos_x, pos_y, tag, state, _door_id, linked_map),
        _required_key_type(required_key_type) {}

    ItemType GetRequiredKeyType() { return _required_key_type; }

private:
    ItemType _required_key_type;
};

