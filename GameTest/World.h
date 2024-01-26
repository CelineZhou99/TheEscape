#pragma once

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

using Dialogue = std::vector<std::string>;
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
	// Getters
	//------------------------------------------------------------------------
	SpawnedRewardsMap& GetSpawnedRewards() { return spawned_rewards; }
	std::vector<unsigned short>& GetUnlockedDoors() { return _unlocked_doors; }
	std::shared_ptr<Player> GetPlayer() const { return player; }
	Scene* GetCurrScene() const { return current_scene.get(); }
	Goal* GetCurrGoal() const { return current_goal.get(); }
	bool HasGameEnded() const { return has_game_ended; }
	bool HasDialogueFinished() const { return text_box->GetIsDialogueFinished(); }
	CSimpleSprite* GetEndScreenSprite() const { return end_screen_sprite.get(); }
	//------------------------------------------------------------------------
	// Setters
	//------------------------------------------------------------------------
	void SetHasGameEnded(bool has_ended) { has_game_ended = has_ended; }
	void SetCurrGoal(std::shared_ptr<Goal> goal) { current_goal = goal; }
	void ResetScene() { current_scene.reset(); }
	void SetCurrScene() { current_scene = std::make_unique<Scene>(current_goal.get()); }
	//------------------------------------------------------------------------
	// Functions for Dialogue
	//------------------------------------------------------------------------
	void NextDialogue() { text_box->NextDialogue(); }
	void SetDialogue(Dialogue* dialogue) { text_box->SetDialogue(dialogue); }
	//------------------------------------------------------------------------
	// Functions for the update loop
	//------------------------------------------------------------------------
	void Update(float deltaTime);
	// returns whether the player will move
	bool CalculatePlayerNextMovement(ColliderBase& collider, FacingDirection& direction, float& player_move_by_x, float& player_move_by_y);
	bool ShouldPlayerMove(ColliderBase& collider, FacingDirection& direction);
	bool ShouldMovableObjectsMove(Actor& actor_to_move, ColliderBase& collider, FacingDirection& direction);
	void UpdateMovableObjects(Actor& actor, FacingDirection direction, GameObject* object);

	bool OnKeyUp(char key, bool& key_variable);
	bool CheckShootControls(FacingDirection& direction);
	void UpdateSpells(float deltaTime);

	void GameEnd(GameEndType game_end_type);
	//------------------------------------------------------------------------
	// Functions for the render loop
	//------------------------------------------------------------------------
	void DrawAllSprites();
	void DrawUI();
	void DrawTextBox();
	
private:
	SpawnedRewardsMap spawned_rewards = {};

	std::vector<unsigned short> _unlocked_doors = {};

	std::shared_ptr<Player> player = nullptr;

	std::unique_ptr<Scene> current_scene = nullptr;
	std::shared_ptr<Goal> current_goal = nullptr;

	std::unique_ptr<CSimpleSprite> end_screen_sprite = nullptr;
	
	std::shared_ptr<TextBox> text_box = nullptr;
	std::shared_ptr<Dialogue> game_start_dialogue = nullptr;

	bool has_game_ended = false;

	bool is_up_pressed = false;
	bool is_down_pressed = false;
	bool is_left_pressed = false;
	bool is_right_pressed = false;
};

