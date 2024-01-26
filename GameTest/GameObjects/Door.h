#pragma once
#include "Actor.h"
#include "../GameObjects/IInteractable.h"
#include "../States/DoorStateLocked.h"
#include "../States/DoorStateUnlocked.h"
#include <unordered_map>

class World;

using DoorStateMap = std::unordered_map<DoorStateType, std::shared_ptr<IDoorState>>;

class Door :
	public Actor, public IInteractable
{
	// context class for door states
public:
	Door(unsigned short id, std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag, DoorStateType state, unsigned short door_id, char* linked_map) :
		Actor(id, renderer, pos_x, pos_y, tag), 
		_door_state_map({ 
			{DoorStateType::LOCKED, std::make_shared<DoorStateLocked>(this)}, 
			{DoorStateType::UNLOCKED, std::make_shared<DoorStateUnlocked>(this)} 
			}),
		_linked_map(linked_map),
		_door_id(door_id),
		_state_type(state) {}

	DoorStateType GetStateType() const { return _state_type; }
	void SetState(DoorStateType state);

	unsigned short GetDoorId() const { return _door_id; }

	char* GetLinkedMap() const { return _linked_map; }

	void OnInteractWithPlayer(World& world) override;

protected:
	DoorStateMap _door_state_map;
	char* _linked_map;
	unsigned short _door_id;
	DoorStateType _state_type;
};

