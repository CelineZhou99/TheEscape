#pragma once

#include "Controllers/PlayerController.h"
#include "GameObjects/Player.h"
#include "Scenes/Scene.h"
#include <vector>
#include "UI/TextBox.h"

#define STARTING_MAP ".\\Data\\Maps\\MapA.txt"
#define NORMAL_MUSIC ".\\Data\\Sounds\\Groovy.wav"
#define END_MUSIC ".\\Data\\Sounds\\Fanfare.wav"
#define END_SCREEN ".\\Data\\Images\\EndScreen.bmp"
#define DEAD_MUSIC ".\\Data\\Sounds\\DeathTheme.wav"
#define DEAD_SCREEN ".\\Data\\Images\\DeadScreen.bmp"
#define PLAYER_START_X 480.0f
#define PLAYER_START_Y 160.0f
#define UI_START_X 32
#define UI_START_Y APP_VIRTUAL_HEIGHT - 32
#define UI_SPACING_X 32
#define UI_SPACING_Y 32

#define TEXT_BOX ".\\Data\\Images\\TextBox.bmp"
#define TEXT_BOX_X 512
#define TEXT_BOX_Y 64

using Dialogue = std::vector<const char*>;

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
	bool CalculatePlayerNextMovement(ICollider& collider, FacingDirection& direction, float& player_move_by_x, float& player_move_by_y);
	bool ShouldPlayerMove(ICollider& collider, FacingDirection& direction);
	bool ShouldMovableObjectsMove(Actor& actor_to_move, ICollider& collider, FacingDirection& direction);
	void UpdateMovableObjects(Actor& actor, FacingDirection direction);
	void InvulnerabilityCountdown(float deltaTime);

	void GameEndEscaped();
	void GameEndDead();
	//------------------------------------------------------------------------
	// Functions for the render loop
	//------------------------------------------------------------------------
	void DrawAllSprites();
	void DrawUI();
	void DrawTextBox();

	std::shared_ptr<PlayerController> player_controller = nullptr;
	std::shared_ptr<Player> player = nullptr;

	std::unique_ptr<Scene> current_scene = nullptr;
	std::shared_ptr<Goal> current_goal = nullptr;

	bool has_game_ended = false;
	std::unique_ptr<CSimpleSprite> end_screen_sprite = nullptr;

	TextBox text_box = TextBox(TEXT_BOX);
	// TODO: ask - since it is only used at the very start, it should be on the stack right?
	Dialogue game_start_dialogue = {
		"Where am I...?", 
		"I can't remember much...", 
		"I can hear the faint sound of birds from that door...",
		"That must be the exit."
	};

	float start_timer = 0.f;
	float stop_timer = 2.f;
};

