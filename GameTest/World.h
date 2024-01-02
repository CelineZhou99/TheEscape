#pragma once

#include "Controllers/PlayerController.h"
#include "GameObjects/Player.h"
#include "Scenes/Scene.h"
#include <vector>

#define PLAYER_START_X 480.0f
#define PLAYER_START_Y 160.0f
#define UI_START_X 32
#define UI_START_Y APP_VIRTUAL_HEIGHT - 32
#define UI_SPACING_X 32
#define UI_SPACING_Y 32

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
	void DrawUI();

	void GameEnd();

	std::shared_ptr<PlayerController> player_controller = nullptr;
	std::shared_ptr<Player> player = nullptr;

	std::unique_ptr<Scene> current_scene = nullptr;
	std::shared_ptr<Goal> current_goal = nullptr;

	bool HasGameEnded = false;
	std::unique_ptr<CSimpleSprite> end_screen_sprite = nullptr;
};

