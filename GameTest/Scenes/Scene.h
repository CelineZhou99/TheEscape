#pragma once
#include <set>
#include "../Observers/ISubscriber.h"
#include "../Observers/Goal.h"
#include "../GameObjects/Door.h"

#define GOAL_CONTEXT "GC"
#define GOAL_DOOR_ID "GD"
#define GOAL_REWARD "GR"

#define GOAL_REWARD_KEY "K"
#define GOAL_REWARD_KEY_ESCAPE "KE"

#define SCENE_OBJECT_FLOOR 'F'
#define SCENE_OBJECT_WALL 'W'
#define SCENE_OBJECT_BOX 'B'
#define SCENE_OBJECT_PRESSURE_PLATE 'P'
#define SCENE_OBJECT_DUNGEON_DOOR 'D'
#define SCENE_OBJECT_PATH 'A'
#define SCENE_OBJECT_KEY 'K'
#define SCENE_OBJECT_KEY_ESCAPE 'E'
#define SCENE_OBJECT_GOAL_REWARD_TILE 'T'
#define SCENE_OBJECT_SLIME 'S'
#define SCENE_OBJECT_RESET_BUTTON 'R'
#define SCENE_OBJECT_GUMMY_BEAR 'G'
#define SCENE_OBJECT_POT 'O'

#define IMAGE_FLOOR ".\\Data\\Images\\Floor.bmp"
#define IMAGE_FLOOR_V2 ".\\Data\\Images\\FloorV2.bmp"
#define IMAGE_WALL ".\\Data\\Images\\Wall.bmp"
#define IMAGE_WALL_V2 ".\\Data\\Images\\WallV2.bmp"
#define IMAGE_BOX ".\\Data\\Images\\Box.bmp"
#define IMAGE_PRESSURE_PLATE ".\\Data\\Images\\PressurePlate.bmp"
#define IMAGE_DUNGEON_DOOR_LOCKED ".\\Data\\Images\\DungeonDoorLocked.bmp"
#define IMAGE_DUNGEON_DOOR_UNLOCKED ".\\Data\\Images\\DungeonDoorUnlocked.bmp"
#define IMAGE_PATH ".\\Data\\Images\\Path.bmp"
#define IMAGE_KEY ".\\Data\\Images\\Key.bmp"
#define IMAGE_KEY_ESCAPE ".\\Data\\Images\\KeyEscape.bmp"
#define IMAGE_GOAL_REWARD_TILE ".\\Data\\Images\\GoalRewardsTile.bmp"
#define IMAGE_SLIME ".\\Data\\Images\\Slime.bmp"
#define IMAGE_RESET_BUTTON ".\\Data\\Images\\ResetButton.bmp"
#define IMAGE_FIREBALL ".\\Data\\Images\\Fireball.bmp"
#define IMAGE_GUMMY_BEAR ".\\Data\\Images\\GummyBear.bmp"
#define IMAGE_POT ".\\Data\\Images\\Pot.bmp"
#define IMAGE_TEXT_BOX ".\\Data\\Images\\TextBox.bmp"

#define SHOOT_SOUND ".\\Data\\Sounds\\Shoot.wav"

#define OBJECT_STATE_INDEX 0
#define OBJECT_ID_INDEX 1 
#define LINKED_MAP_ID_INDEX 2

#define MAP_WIDTH 16
#define MAP_HEIGHT 12

class Slime;

enum LayerType : uint8_t
{
	BACKGROUND,
	MIDDLEGROUND,
	FOREGROUND,
	CHARACTERS,
	SPELLS,
	COUNT,
};

using GameObjectPtr = std::shared_ptr<GameObject>;
using RendererPtr = std::shared_ptr<Renderer>;

using SceneLayersList = std::vector<std::vector<GameObjectPtr>>;
using ObjectsList = std::vector<GameObjectPtr>;
using GoalTypeMap = std::unordered_map<std::string, GoalType>;
using DoorStateContextMap = std::unordered_map<char, DoorStateType>;
using MapIdMap = std::unordered_map<char, char*>;

class Scene : public ISubscriber
{
public:
	Scene(Goal* goal) :
		_goal_type_mapping({
			{"N", GoalType::GOAL_NONE},
			{"P", GoalType::GOAL_PRESSURE_PLATE},
			{"S", GoalType::GOAL_SLIME},
			}),
		_door_state_mapping({
			{'L', DoorStateType::LOCKED},
			{'U', DoorStateType::UNLOCKED},
			}),
		_map_id_mapping({
			{'A', ".\\Data\\Maps\\MapA.txt"},
			{'B', ".\\Data\\Maps\\MapB.txt"},
			{'C', ".\\Data\\Maps\\MapC.txt"},
			{'D', ".\\Data\\Maps\\MapD.txt"},
			{'E', ".\\Data\\Maps\\MapE.txt"},
			{'F', ".\\Data\\Maps\\MapF.txt"},
			{'G', ".\\Data\\Maps\\MapG.txt"},
			}),
		_map(),
		_scene_layers({}),
		_goal_doors({}),
		_goal(goal),
		_goal_context(""),
		_map_file_name(""),
		_id(0),
		_object_state(' '),
		_object_id(' '),
		_linked_map_id(' ')
	{
		Init();
	}

	void Init();

	void SetUpSceneLayers();
	SceneLayersList GetSceneLayers() const { return _scene_layers; }
	void AddToSceneLayers(GameObjectPtr object, LayerType layer);
	void RemoveFromSceneLayers(GameObject* object, LayerType layer);

	std::set<int> ReadContextFromFile(std::istringstream& iss, std::string& word);

	void LoadMap(const char* file_name_text);
	void MakeFloor(float i, float j);
	void MakeWall(float i, float j, int map_w, int map_h);
	void MakeBox(float i, float j, int map_w, int map_h);
	void MakePressurePlate(float i, float j);
	void MakeDungeonDoor(float i, float j, std::string& word, std::set<int> goal_door_ids, char* token, int map_w, int map_h);
	void MakePath(float i, float j, std::string& word, char* token, int map_w, int map_h);
	void MakeGoalRewardsTile(float i, float j);
	std::shared_ptr<Item> MakeKey(float i, float j);
	std::shared_ptr<Item> MakeKeyEscape(float i, float j);
	void MakeSlime(float i, float j);
	void MakeResetButton(float i, float j, int map_w, int map_h);
	void MakeFireball(float i, float j, FacingDirection direction);
	void MakeGummyBear(float i, float j, int map_w, int map_h);
	void MakePot(float i, float j, int map_w, int map_h);

	std::shared_ptr<Actor> GetDoorWithId(int id);
	Goal* GetGoal() const { return _goal; }
	GoalType GetGoalType();

	bool IsSpaceFree(Vector2D& position);
	void MoveObjectPositionInMap(Vector2D& old_position, Vector2D& new_position, GameObject* object);
	void RemoveItemFromMap(Vector2D& position, GameObject* object);
	void GetCoordinateByPosition(Vector2D& position, int& map_w, int& map_h);
	Vector2D GetPositionByCoordinate(int map_w, int map_h) const;

	void UpdateSubscriber() override;

	int GenerateRandomBetween(int min, int max);

	const char* GetMapFileName() const { return _map_file_name; }

	unsigned short AllocateId() { return _id++; }

	void SpawnFireball(Vector2D& player_position, FacingDirection direction);

private:
	void RemoveObjectInMap(int map_w, int map_h, GameObject* object);

	void StoreResetButtonData();

	GoalTypeMap _goal_type_mapping;
	DoorStateContextMap _door_state_mapping;
	MapIdMap _map_id_mapping;

	ObjectsList _map[MAP_WIDTH][MAP_HEIGHT] = { {} };

	SceneLayersList _scene_layers;
	std::vector<std::shared_ptr<Door>> _goal_doors;
	std::vector<char> _context_reading_order = { _object_state, _object_id, _linked_map_id };
	
	std::string _goal_context;
	Goal* _goal;

	const char* _map_file_name;

	unsigned short _id;

	char _object_state;
	char _object_id;
	char _linked_map_id;
};

