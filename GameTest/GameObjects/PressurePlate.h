#pragma once
#include "Actor.h"
#include "../States/PressurePlateState.h"
#include "../States/PressurePlateStateOn.h"
#include "../States/PressurePlateStateOff.h"
#include <unordered_map>

using PressurePlateStateMap = std::unordered_map<PressurePlateStateType, std::shared_ptr<PressurePlateState>>;

class PressurePlate :
    public Actor
{
public:
    PressurePlate(std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag) : Actor(renderer, pos_x, pos_y, tag), 
        _state_type(PressurePlateStateType::OFF)
    {
        std::shared_ptr<PressurePlateStateOn> pressure_plate_state_on = std::make_shared<PressurePlateStateOn>(this);
        std::shared_ptr<PressurePlateStateOff> pressure_plate_state_off = std::make_shared<PressurePlateStateOff>(this);
        _pressure_plate_state_map[PressurePlateStateType::ON] = pressure_plate_state_on;
        _pressure_plate_state_map[PressurePlateStateType::OFF] = pressure_plate_state_off;
    }

    void SetState(PressurePlateStateType state, Goal* goal);
    PressurePlateStateType GetStateType() { return _state_type; }

protected:
    PressurePlateStateMap _pressure_plate_state_map;
    PressurePlateStateType _state_type;
};

