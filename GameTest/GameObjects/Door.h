#pragma once
#include "Actor.h"
#include "../States/DoorState.h"
#include "../States/DoorStateLocked.h"
#include "../States/DoorStateUnlocked.h"
#include <unordered_map>

class Door :
	public Actor
{
	// context class for door states
public:
	Door(std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag, DoorStateType state) : Actor(renderer, pos_x, pos_y, tag)
	{
		std::shared_ptr<DoorStateLocked> door_state_locked = std::make_shared<DoorStateLocked>(this);
		std::shared_ptr<DoorStateUnlocked> door_state_unlocked = std::make_shared<DoorStateUnlocked>(this);
		_door_state_map.insert(std::make_pair(DoorStateType::LOCKED, door_state_locked));
		_door_state_map.insert(std::make_pair(DoorStateType::UNLOCKED, door_state_unlocked));

		_state_type = state;
	}

	void SetState(DoorStateType state);
	DoorStateType GetStateType() { return _state_type; }

	void OnPlayerCollision(World& world);

protected:
	std::unordered_map<DoorStateType, std::shared_ptr<DoorState>> _door_state_map;
	DoorStateType _state_type;
};

