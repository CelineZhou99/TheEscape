#pragma once
#include "Door.h"
class Path :
    public Door
{
public:
    Path(std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag, unsigned short id, char* linked_map) : 
        Door(renderer, pos_x, pos_y, tag, DoorStateType::UNLOCKED, id, linked_map) {}
};

