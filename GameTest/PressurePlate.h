#pragma once
#include "GameObjects/Actor.h"
#include "PressurePlateState.h"
#include "PressurePlateStateOn.h"
#include "PressurePlateStateOff.h"
#include <unordered_map>

class PressurePlate :
    public Actor
{
public:
    PressurePlate(std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag) : Actor(renderer, pos_x, pos_y, tag) 
    {
        std::shared_ptr<PressurePlateStateOn> pressure_plate_state_on = std::make_shared<PressurePlateStateOn>(this);
        std::shared_ptr<PressurePlateStateOff> pressure_plate_state_off = std::make_shared<PressurePlateStateOff>(this);
        _pressure_plate_state_map.insert(std::make_pair(PressurePlateStateType::ON, pressure_plate_state_on));
        _pressure_plate_state_map.insert(std::make_pair(PressurePlateStateType::OFF, pressure_plate_state_off));

        _state_type = PressurePlateStateType::OFF;
    }

    void SetState(PressurePlateStateType state, Goal* goal);
    PressurePlateStateType GetStateType() { return _state_type; }

protected:
    std::unordered_map<PressurePlateStateType, std::shared_ptr<PressurePlateState>> _pressure_plate_state_map;
    PressurePlateStateType _state_type;
};

