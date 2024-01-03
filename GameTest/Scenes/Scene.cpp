#include "stdafx.h"
#include "Scene.h"
#include "../GameObjects/Renderer.h"
#include "../GameObjects/Path.h"
#include "../GameObjects/DungeonDoor.h"
#include "../GameObjects/PressurePlate.h"
#include "../GameObjects/Key.h"

void Scene::Init()
{
	SetUpSceneLayers();
}

void Scene::SetUpSceneLayers()
{
	for (size_t i = 0; i < LayerType::COUNT; ++i)
	{
		std::vector<std::shared_ptr<GameObject>> new_layer = {};
		_scene_layers.push_back(new_layer);
	}
}

void Scene::AddToSceneLayers(std::shared_ptr<GameObject> object, LayerType layer)
{
	_scene_layers[layer].push_back(object);
}

void Scene::RemoveFromSceneLayers(GameObject* object, LayerType layer)
{
	std::vector<std::shared_ptr<GameObject>>::iterator it =
		std::find_if(_scene_layers[layer].begin(), _scene_layers[layer].end(), [object](const std::shared_ptr<GameObject>& o)
			{
				return (o->GetRenderer()->GetFileName() == object->GetRenderer()->GetFileName()) &&
					(o->GetTransform()->X() == object->GetTransform()->X()) &&
					(o->GetTransform()->Y() == object->GetTransform()->Y());
			});
	if (it != _scene_layers[layer].end())
	{
		_scene_layers[layer].erase(it);
	}
}

std::set<int> Scene::ReadContextFromFile(std::istringstream& iss, std::string& word)
{
	std::set<int> goal_door_ids = {};
	while (iss >> word)
	{
		// TODO: SWITCH TO SEPARATE BY ':'
		std::string context = word.substr(0, 2);
		// check the goal context of the current map
		// there can only be 1 goal context for now e.g. pressure plate, monsters
		if (context == GOAL_CONTEXT)
		{
			_goal_context = word.substr(3, 1);
		}
		// check the goal doors (doors that will unlock when the goal is reached) of the current map
		else if (context == GOAL_DOOR_ID)
		{
			std::string goal_doors = word.substr(3, word.size() - 3);
			char* c_goal_doors = &goal_doors[0];
			char* token = std::strtok(c_goal_doors, ",");

			while (token != NULL)
			{
				int id = token[0];
				goal_door_ids.insert(id);
				token = std::strtok(NULL, ",");
			}
		}
	}
	return goal_door_ids;
}

void Scene::LoadMap(const char* file_name_text)
{
	std::ifstream infile(file_name_text);
	std::string line = "";
	std::string word = "";

	std::getline(infile, line);
	std::istringstream iss(line);

	std::set<int> goal_door_ids = ReadContextFromFile(iss, word);

	float i = 0;

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		float j = 0;
		while (iss >> word)
		{
			char* w = &word[0];
			char* token = std::strtok(w, ":");

			char object_type = token[0];
			token = std::strtok(NULL, ":");
			
			if (object_type == SCENE_OBJECT_FLOOR)
			{
				MakeFloor(i, j);
			}
			else if (object_type == SCENE_OBJECT_WALL)
			{
				MakeWall(i, j);
			}
			else if (object_type == SCENE_OBJECT_BOX)
			{
				MakeBox(i, j);
			}
			else if (object_type == SCENE_OBJECT_PRESSURE_PLATE)
			{
				MakePressurePlate(i, j);
			}
			else if (object_type == SCENE_OBJECT_DUNGEON_DOOR)
			{
				MakeDungeonDoor(i, j, word, goal_door_ids, token);
			}
			else if (object_type == SCENE_OBJECT_PATH)
			{
				MakePath(i, j, word, token);
			}
			else if (object_type == SCENE_OBJECT_KEY)
			{
				MakeFloor(i, j);

				std::shared_ptr<Renderer> key_renderer = std::make_shared<Renderer>(IMAGE_KEY, 1, 1, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF);
				std::shared_ptr<Key> key = std::make_shared<Key>(key_renderer, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF, TagType::ITEM, ItemType::KEY);
				_scene_layers[LayerType::FOREGROUND].push_back(key);
			}
			else if (object_type == SCENE_OBJECT_KEY_ESCAPE)
			{
				MakeFloor(i, j);

				std::shared_ptr<Renderer> key_renderer = std::make_shared<Renderer>(IMAGE_KEY_ESCAPE, 1, 1, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF);
				std::shared_ptr<Key> key = std::make_shared<Key>(key_renderer, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF, TagType::ITEM, ItemType::KEY_ESCAPE);
				_scene_layers[LayerType::FOREGROUND].push_back(key);
			}
			j += IMAGE_SIZE_FULL;
		}
		i += IMAGE_SIZE_FULL;
	}
}

void Scene::MakeFloor(float i, float j)
{
	std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>(IMAGE_FLOOR, 1, 1, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF);
	std::shared_ptr<GameObject> floor =
		std::make_shared<GameObject>(renderer, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF, TagType::STATIC_OBJECT);
	_scene_layers[LayerType::BACKGROUND].push_back(floor);
}

void Scene::MakeWall(float i, float j)
{
	std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>(IMAGE_WALL, 1, 1, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF);
	std::shared_ptr<Actor> wall = std::make_shared<Actor>(renderer, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF, TagType::STATIC_OBJECT);
	_scene_layers[LayerType::MIDDLEGROUND].push_back(wall);
}

void Scene::MakeBox(float i, float j)
{
	MakeFloor(i, j);

	std::shared_ptr<Renderer> box_renderer = std::make_shared<Renderer>(IMAGE_BOX, 1, 1, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF);
	std::shared_ptr<Actor> box = std::make_shared<Actor>(box_renderer, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF, TagType::MOVABLE_OBJECT);
	box->GetRenderer()->GetSprite()->SetScale(0.9f);
	_scene_layers[LayerType::FOREGROUND].push_back(box);
}

void Scene::MakePressurePlate(float i, float j)
{
	MakeFloor(i, j);

	std::shared_ptr<Renderer> plate_renderer =
		std::make_shared<Renderer>(IMAGE_PRESSURE_PLATE, 1, 1, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF);
	std::shared_ptr<PressurePlate> plate =
		std::make_shared<PressurePlate>(plate_renderer, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF, TagType::PLATE);
	_scene_layers[LayerType::MIDDLEGROUND].push_back(plate);

	// TODO: CHANGE THIS TO GOAL TYPE MAPPING
	if (_goal_context == GOAL_CONTEXT_PRESSURE_PLATE)
	{
		_goal->IncrementContextCount();
	}
}

void Scene::MakeDungeonDoor(float i, float j, std::string& word, std::set<int> goal_door_ids, char* token)
{
	MakeFloor(i, j);

	int index = 0;
	while (token != NULL)
	{
		_context_reading_order[index] = token[0];
		token = std::strtok(NULL, ":");
		++index;
	}

	int id = atoi(&_context_reading_order[OBJECT_ID_INDEX]);

	std::unordered_map<char, DoorStateType>::iterator d_it = _door_state_mapping.find(_context_reading_order[OBJECT_STATE_INDEX]);
	DoorStateType type = DoorStateType::LOCKED;
	if (d_it != _door_state_mapping.end())
	{
		type = d_it->second;
	}

	std::shared_ptr<Renderer> door_renderer = nullptr;
	if (type == DoorStateType::LOCKED)
	{
		door_renderer = std::make_shared<Renderer>(IMAGE_DUNGEON_DOOR_LOCKED, 1, 1, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF);
	}
	else if (type == DoorStateType::UNLOCKED)
	{
		door_renderer = std::make_shared<Renderer>(IMAGE_DUNGEON_DOOR_UNLOCKED, 1, 1, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF);
	}

	std::unordered_map<char, char*>::iterator it = _map_id_mapping.find(_context_reading_order[LINKED_MAP_ID_INDEX]);
	char* linked_map = {};
	if (it != _map_id_mapping.end())
	{
		linked_map = it->second;
	}

	ItemType required_key_type = id == 0 ? ItemType::KEY_ESCAPE : ItemType::KEY;

	std::shared_ptr<DungeonDoor> door = 
		std::make_shared<DungeonDoor>(door_renderer, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF, TagType::DOOR, type, id, linked_map, required_key_type);
	_scene_layers[LayerType::MIDDLEGROUND].push_back(door);

	if (goal_door_ids.find(id) != goal_door_ids.end())
	{
		_goal_doors.push_back(door);
	}
}

void Scene::MakePath(float i, float j, std::string& word, char* token)
{
	MakeFloor(i, j);

	int index = 0;
	while (token != NULL)
	{
		_context_reading_order[index] = token[0];
		token = std::strtok(NULL, ":");
		++index;
	}
	int id = atoi(&_context_reading_order[OBJECT_ID_INDEX]);

	std::unordered_map<char, char*>::iterator it = _map_id_mapping.find(_context_reading_order[LINKED_MAP_ID_INDEX]);
	char* linked_map = {};
	if (it != _map_id_mapping.end())
	{
		linked_map = it->second;
	}

	std::shared_ptr<Renderer> path_renderer =
		std::make_shared<Renderer>(IMAGE_PATH, 1, 1, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF);
	std::shared_ptr<Path> path =
		std::make_shared<Path>(path_renderer, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF, TagType::DOOR, id, linked_map);
	_scene_layers[LayerType::MIDDLEGROUND].push_back(path);
}

std::shared_ptr<Actor> Scene::GetDoorWithId(int id)
{
	for (std::shared_ptr<GameObject> object : _scene_layers.at(LayerType::MIDDLEGROUND))
	{
		Actor& actor = static_cast<Actor&>(*object.get());
		if (actor.GetTag() == TagType::DOOR)
		{
			Door& door = static_cast<Door&>(actor);
			if (door.GetId() == id)
			{
				return std::make_shared<Actor>(actor);
			}
		}
	}
	return nullptr;
}

GoalType Scene::GetGoalType()
{
	std::unordered_map<std::string, GoalType>::iterator it = _goal_type_mapping.find(_goal_context);
	if (it != _goal_type_mapping.end())
	{
		return it->second;
	}
	return GoalType::GOAL_NONE;
}

bool Scene::IsSpaceFree(Vector2D& position)
{
	for (std::shared_ptr<GameObject> object : _scene_layers.at(LayerType::MIDDLEGROUND))
	{
		if (object->GetTransform()->X() == position.X() && object->GetTransform()->Y() == position.Y())
		{
			return false;
		}
	}

	for (std::shared_ptr<GameObject> object : _scene_layers.at(LayerType::FOREGROUND))
	{
		if (object->GetTransform()->X() == position.X() && object->GetTransform()->Y() == position.Y())
		{
			return false;
		}
	}

	return true;
}

void Scene::Update()
{
	if (_goal->IsGoalComplete())
	{
		for (std::shared_ptr<Door> door : _goal_doors)
		{
			// unlock all goal doors
			door->SetState(DoorStateType::UNLOCKED);
		}
	}
	else
	{
		for (std::shared_ptr<Door> door : _goal_doors)
		{
			// unlock all goal doors
			door->SetState(DoorStateType::LOCKED);
		}
	}
}


