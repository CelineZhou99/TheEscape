#pragma once

#include "PlayerController.h"

class World
{
	// global container 
public:
	~World() 
	{
		delete player_controller;
		delete player;
	}

	void Init();

	void CalculateNextPlayerMovement(Collider& collider, FacingDirection& direction, float& player_move_by_x, float& player_move_by_y);
	bool ShouldPlayerMove(Collider& collider, FacingDirection& direction);
	void UpdateMovableObjects(Actor* actor, FacingDirection direction);

	PlayerController* player_controller = nullptr;
	Actor* player = nullptr;
	std::vector<Actor*> actors = {};
	std::vector<GameObject*> game_objects = {};
};

