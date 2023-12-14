#pragma once
#include "Actor.h"
#include "../States/DoorState.h"
#include "../States/DoorStateLocked.h"
#include "../States/DoorStateUnlocked.h"
#include <unordered_map>

using DoorStateMap = std::unordered_map<DoorStateType, std::shared_ptr<DoorState>>;

class Door :
	public Actor
{
	// context class for door states
public:
	Door(std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag, DoorStateType state) : Actor(renderer, pos_x, pos_y, tag), _state_type(state)
	{
		std::shared_ptr<DoorStateLocked> door_state_locked = std::make_shared<DoorStateLocked>(this);
		std::shared_ptr<DoorStateUnlocked> door_state_unlocked = std::make_shared<DoorStateUnlocked>(this);
		_door_state_map[DoorStateType::LOCKED] = door_state_locked;
		_door_state_map[DoorStateType::UNLOCKED] = door_state_unlocked;
	}

	void SetState(DoorStateType state);
	DoorStateType GetStateType() { return _state_type; }

	void OnPlayerCollision(World& world);

protected:
	DoorStateMap _door_state_map;
	DoorStateType _state_type;
};

