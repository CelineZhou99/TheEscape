#pragma once
#include "Controller.h"
#include "../GameObjects/Slime.h"

class SlimeController :
    public Controller
{
public:
    SlimeController(Slime* actor) : Controller(actor) {}

    void UpdateControlledActorPosition(float move_by_x, float move_by_y, FacingDirection direction) override;
    void SetControlledActorPosition(float x, float y, FacingDirection direction) override;
};

