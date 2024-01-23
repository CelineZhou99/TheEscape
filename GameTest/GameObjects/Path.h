#pragma once
#include "Door.h"
class Path :
    public Door
{
public:
    Path(unsigned short id, std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag, unsigned short door_id, char* linked_map) :
        Door(id, renderer, pos_x, pos_y, tag, DoorStateType::UNLOCKED, door_id, linked_map) {}
};

