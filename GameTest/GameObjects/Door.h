#pragma once
#include "Actor.h"
#include "../GameObjects/IInteractable.h"
#include "../States/DoorStateLocked.h"
#include "../States/DoorStateUnlocked.h"
#include <unordered_map>

using DoorStateMap = std::unordered_map<DoorStateType, std::shared_ptr<IDoorState>>;

class Door :
	public Actor, public IInteractable
{
	// context class for door states
public:
	Door(std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag, DoorStateType state, int id, char* linked_map) : 
		Actor(renderer, pos_x, pos_y, tag), 
		_door_state_map({ 
			{DoorStateType::LOCKED, std::make_shared<DoorStateLocked>(this)}, 
			{DoorStateType::UNLOCKED, std::make_shared<DoorStateUnlocked>(this)} 
			}),
		_state_type(state),
		_id(id),
		_linked_map(linked_map) {}

	DoorStateType GetStateType() { return _state_type; }
	void SetState(DoorStateType state);

	int GetId() { return _id; }

	char* GetLinkedMap() { return _linked_map; }

	void OnInteractWithPlayer(World& world) override;

protected:
	DoorStateMap _door_state_map;
	DoorStateType _state_type;
	int _id;
	char* _linked_map;
};

