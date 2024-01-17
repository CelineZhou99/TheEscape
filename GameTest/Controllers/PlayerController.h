#pragma once
#include "Controller.h"
#include "../GameObjects/Player.h"

class PlayerController :
    public Controller
{
public:
    PlayerController(Player* actor) : Controller(actor) {}
    
    void UpdateControlledActorPosition(float move_by_x, float move_by_y, FacingDirection direction) override;
    void SetControlledActorPosition(float x, float y, FacingDirection direction) override;

    Player* GetControlledActor();
};

