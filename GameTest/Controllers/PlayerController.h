#pragma once
#include "Controller.h"
#include "../GameObjects/Player.h"

class PlayerController :
    public Controller
{
public:
    PlayerController(Player* actor) : Controller(actor) {}
    
    void UpdatePlayerPosition(float move_by_x, float move_by_y, FacingDirection direction);
    void SetPlayerPosition(float x, float y, FacingDirection direction);

    Player* GetControlledActor();
};

