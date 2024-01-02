#pragma once
#include "Door.h"

class DungeonDoor :
    public Door
{
public:
    DungeonDoor(std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag, DoorStateType state, int id, char* linked_map) : Door(renderer, pos_x, pos_y, tag, state, id, linked_map) {}
};

