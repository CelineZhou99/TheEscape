#pragma once

#include "PlayerController.h"
#include "Player.h"
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
	void Update(float deltaTime);
	void CalculateNextPlayerMovement(Collider& collider, FacingDirection& direction, float& player_move_by_x, float& player_move_by_y);
	bool ShouldPlayerMove(Collider& collider, FacingDirection& direction);
	void UpdateMovableObjects(Actor& actor, FacingDirection direction);
	//------------------------------------------------------------------------
	// Functions for the render loop
	//------------------------------------------------------------------------
	void DrawAllSprites();

	std::shared_ptr<PlayerController> player_controller = nullptr;
	std::shared_ptr<Player> player = nullptr;
	std::vector<std::shared_ptr<GameObject>> background_objects = {};
	std::vector<std::shared_ptr<Actor>> middleground_objects = {};
	std::vector<std::shared_ptr<Actor>> foreground_objects = {};
};

