#pragma once
#include "Door.h"
class InvisibleDoor :
    public Door
{
public:
    InvisibleDoor(std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag, DoorStateType state) : Door(renderer, pos_x, pos_y, tag, state) {}
};

