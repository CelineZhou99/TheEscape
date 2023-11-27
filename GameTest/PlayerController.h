#pragma once
#include "Controller.h"
class PlayerController :
    public Controller
{
public:
    PlayerController(Actor* actor) : Controller(actor) {}
    
    bool IsMoving();
    void UpdatePlayerPosition(float move_by_x, float move_by_y, FacingDirection direction);
};

