#pragma once
#include <math.h>  
#include <set>
#include "../GameObjects/Actor.h"
#include "../Observers/Subscriber.h"
#include "../Observers/Goal.h"
#include "../GameObjects/Door.h"

#define GOAL_CONTEXT "GC"
#define GOAL_DOOR_ID "GD"

#define SCENE_OBJECT_FLOOR 'F'
#define SCENE_OBJECT_WALL 'W'
#define SCENE_OBJECT_BOX 'B'
#define SCENE_OBJECT_PRESSURE_PLATE 'P'
#define SCENE_OBJECT_DUNGEON_DOOR 'D'
#define SCENE_OBJECT_PATH 'A'
#define SCENE_OBJECT_KEY 'K'
#define SCENE_OBJECT_KEY_ESCAPE 'E'

#define GOAL_CONTEXT_PRESSURE_PLATE "P"

#define IMAGE_FLOOR ".\\Data\\Images\\Floor.bmp"
#define IMAGE_WALL ".\\Data\\Images\\Wall.bmp"
#define IMAGE_BOX ".\\Data\\Images\\Box.bmp"
#define IMAGE_PRESSURE_PLATE ".\\Data\\Images\\PressurePlate.bmp"
#define IMAGE_DUNGEON_DOOR_LOCKED ".\\Data\\Images\\DungeonDoorLocked.bmp"
#define IMAGE_DUNGEON_DOOR_UNLOCKED ".\\Data\\Images\\DungeonDoorUnlocked.bmp"
#define IMAGE_PATH ".\\Data\\Images\\Path.bmp"
#define IMAGE_KEY ".\\Data\\Images\\Key.bmp"
#define IMAGE_KEY_ESCAPE ".\\Data\\Images\\KeyEscape.bmp"

#define OBJECT_STATE_INDEX 0
#define OBJECT_ID_INDEX 1 
#define LINKED_MAP_ID_INDEX 2

enum LayerType
{
	BACKGROUND,
	MIDDLEGROUND,
	FOREGROUND,
	CHARACTERS,
	COUNT,
};

class Scene : public Subscriber
{
public:
	Scene(Goal* goal) : _scene_layers({}), _goal_doors({}), _goal(goal),
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
			}),
		_goal_type_mapping({
			{"N", GoalType::GOAL_NONE},
			{"P", GoalType::GOAL_PRESSURE_PLATE},
			})
	{
		Init();
	}

	void Init();

	void SetUpSceneLayers();
	std::vector<std::vector<std::shared_ptr<GameObject>>> GetSceneLayers() { return _scene_layers; }
	void AddToSceneLayers(std::shared_ptr<GameObject> object, LayerType layer);
	void RemoveFromSceneLayers(GameObject* object, LayerType layer);

	std::set<int> ReadContextFromFile(std::istringstream& iss, std::string& word);

	// TODO: 
	// have a grid representation of the objects in the scene e.g. 2d array
	// // then can use that to check if some objects are overlapping (could be useful) 
	void LoadMap(const char* file_name_text);
	void MakeFloor(float i, float j);
	void MakeWall(float i, float j);
	void MakeBox(float i, float j);
	void MakePressurePlate(float i, float j);
	void MakeDungeonDoor(float i, float j, std::string& word, std::set<int> goal_door_ids, char* token);
	void MakePath(float i, float j, std::string& word, char* token);

	std::shared_ptr<Actor> GetDoorWithId(int id);
	GoalType GetGoalType();

	bool IsSpaceFree(Vector2D& position);

	void Update() override;



private:
	std::vector<std::vector<std::shared_ptr<GameObject>>> _scene_layers;

	std::vector<std::shared_ptr<Door>> _goal_doors;
	Goal* _goal;

	std::unordered_map<char, DoorStateType> _door_state_mapping;
	std::unordered_map<char, char*> _map_id_mapping;

	std::string _goal_context = {};
	std::unordered_map<std::string, GoalType> _goal_type_mapping;

	char object_state = ' ';
	char object_id = ' ';
	char linked_map_id = ' ';
	std::vector<char> _context_reading_order = { object_state, object_id, linked_map_id };
};

