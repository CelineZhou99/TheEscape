#pragma once

#include "Controllers/PlayerController.h"
#include "GameObjects/Player.h"
#include "Scenes/Scene.h"
#include <vector>

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
	// returns whether the player will move
	bool CalculatePlayerNextMovement(Collider& collider, FacingDirection& direction, float& player_move_by_x, float& player_move_by_y);
	bool ShouldActorMove(Actor& actor_to_move, Collider& collider, FacingDirection& direction);
	bool ShouldMovableObjectsMove(Actor& actor_to_move, Collider& collider, FacingDirection& direction);
	void UpdateMovableObjects(Actor& actor, FacingDirection direction);
	//------------------------------------------------------------------------
	// Functions for the render loop
	//------------------------------------------------------------------------
	void DrawAllSprites();

	void GameEnd();

	std::shared_ptr<PlayerController> player_controller = nullptr;
	std::shared_ptr<Player> player = nullptr;

	std::unique_ptr<Scene> current_scene = nullptr;
	std::shared_ptr<Goal> current_goal = nullptr;

	bool HasGameEnded = false;
	std::unique_ptr<CSimpleSprite> end_screen_sprite = nullptr;
};

