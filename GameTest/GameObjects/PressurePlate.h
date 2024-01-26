#pragma once
#include "Actor.h"
#include "../States/PressurePlateStateOn.h"
#include "../States/PressurePlateStateOff.h"
#include <unordered_map>

class Goal;

using PressurePlateStateMap = std::unordered_map<PressurePlateStateType, std::shared_ptr<IPressurePlateState>>;

class PressurePlate :
    public Actor
{
public:
    PressurePlate(unsigned short id, std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag) :
        Actor(id, renderer, pos_x, pos_y, tag), 
        _pressure_plate_state_map({ 
            {PressurePlateStateType::ON, std::make_shared<PressurePlateStateOn>(this)}, 
            {PressurePlateStateType::OFF, std::make_shared<PressurePlateStateOff>(this)} 
            }),
        _state_type(PressurePlateStateType::OFF) {}
    
    PressurePlateStateType GetStateType() const { return _state_type; }
    void SetState(PressurePlateStateType state, Goal* goal, bool is_reset = false);

protected:
    PressurePlateStateMap _pressure_plate_state_map;
    PressurePlateStateType _state_type;
};

