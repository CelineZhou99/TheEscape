#pragma once

#include "Controllers/PlayerController.h"
#include "GameObjects/Player.h"
#include "Scenes/Scene.h"
#include "UI/TextBox.h"
#include <vector>

#define STARTING_MAP ".\\Data\\Maps\\MapA.txt"
#define NORMAL_MUSIC ".\\Data\\Sounds\\Groovy.wav"
#define END_MUSIC ".\\Data\\Sounds\\Fanfare.wav"
#define END_SCREEN ".\\Data\\Images\\EndScreen.bmp"
#define DEAD_MUSIC ".\\Data\\Sounds\\DeathTheme.wav"
#define DEAD_SCREEN ".\\Data\\Images\\DeadScreen.bmp"
#define BOX_MOVE_SOUND ".\\Data\\Sounds\\BoxMove.wav"
#define PLAYER_START_X 480.0f
#define PLAYER_START_Y 160.0f
#define UI_START_X 32
#define UI_START_Y APP_VIRTUAL_HEIGHT - 32
#define UI_SPACING_X 32
#define UI_SPACING_Y 32

#define TEXT_BOX_X 512
#define TEXT_BOX_Y 64

class Fireball;

using Dialogue = std::vector<const char*>;
using SpawnedRewardsMap = std::unordered_map<const char*, std::shared_ptr<Item>>;
using GameObjectPtr = std::shared_ptr<GameObject>;

enum GameEndType : uint8_t
{
	ESCAPED,
	DEAD,
};

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

	void CheckShootControls();
	void UpdateSpells();
	void CheckSpellCollision(Fireball& fireball);

	void GameEnd(GameEndType game_end_type);
	//------------------------------------------------------------------------
	// Functions for the render loop
	//------------------------------------------------------------------------
	void DrawAllSprites();
	void DrawUI();
	void DrawTextBox();
	//------------------------------------------------------------------------
	// Variables
	//------------------------------------------------------------------------
	SpawnedRewardsMap spawned_rewards = {};

	std::vector<unsigned short> _unlocked_doors = {};

	std::shared_ptr<PlayerController> player_controller = nullptr;
	std::shared_ptr<Player> player = nullptr;

	std::unique_ptr<Scene> current_scene = nullptr;
	std::shared_ptr<Goal> current_goal = nullptr;

	std::unique_ptr<CSimpleSprite> end_screen_sprite = nullptr;
	
	std::shared_ptr<TextBox> text_box = nullptr;
	std::shared_ptr<Dialogue> game_start_dialogue = nullptr;

	float start_timer = 0.f;
	float stop_timer = 2.f;

	bool has_game_ended = false;

	bool is_up_pressed = false;
	bool is_down_pressed = false;
	bool is_left_pressed = false;
	bool is_right_pressed = false;
};

