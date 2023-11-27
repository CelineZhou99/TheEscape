#pragma once

#include "PlayerController.h"

class World
{
	// global container 
public:
	//------------------------------------------------------------------------
	// Functions for the init
	//------------------------------------------------------------------------
	void Init();
	//------------------------------------------------------------------------
	// Functions for the update loop
	//------------------------------------------------------------------------
	void CalculateNextPlayerMovement(std::shared_ptr<Collider> collider, FacingDirection& direction, float& player_move_by_x, float& player_move_by_y);
	bool ShouldPlayerMove(std::shared_ptr<Collider> collider, FacingDirection& direction);
	void UpdateMovableObjects(std::shared_ptr<Actor> actor, FacingDirection direction);
	//------------------------------------------------------------------------
	// Functions for the render loop
	//------------------------------------------------------------------------
	void DrawAllSprites();

	std::shared_ptr<PlayerController> player_controller = nullptr;
	std::shared_ptr<Actor> player = nullptr;
	std::vector<std::shared_ptr<Actor>> actors = {};
	std::vector<std::shared_ptr<GameObject>> game_objects = {};
};

