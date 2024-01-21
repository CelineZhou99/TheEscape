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
	Door(std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag, DoorStateType state, unsigned short id, char* linked_map) : 
		Actor(renderer, pos_x, pos_y, tag), 
		_door_state_map({ 
			{DoorStateType::LOCKED, std::make_shared<DoorStateLocked>(this)}, 
			{DoorStateType::UNLOCKED, std::make_shared<DoorStateUnlocked>(this)} 
			}),
		_linked_map(linked_map),
		_id(id),
		_state_type(state) {}

	DoorStateType GetStateType() { return _state_type; }
	void SetState(DoorStateType state);

	unsigned short GetId() { return _id; }

	char* GetLinkedMap() { return _linked_map; }

	void OnInteractWithPlayer(World& world) override;

protected:
	DoorStateMap _door_state_map;
	char* _linked_map;
	unsigned short _id;
	DoorStateType _state_type;
};

