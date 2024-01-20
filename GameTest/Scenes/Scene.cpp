#include "stdafx.h"
#include "Scene.h"
#include "../GameObjects/Renderer.h"
#include "../GameObjects/Path.h"
#include "../GameObjects/DungeonDoor.h"
#include "../GameObjects/PressurePlate.h"
#include "../GameObjects/Key.h"
#include "../GameObjects/Slime.h"
#include "../GameObjects/ResetButton.h"
#include <random>

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
	// TODO : CHANGE THIS TO ID 
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
				int id = atoi(&token[0]);
				goal_door_ids.insert(id);
				token = std::strtok(NULL, ",");
			}
		}
		else if (context == GOAL_REWARD)
		{
			std::string goal_reward = word.substr(3, word.size() - 3);
			_goal->SetGoalReward(goal_reward);
		}
	}
	return goal_door_ids;
}

void Scene::LoadMap(const char* file_name_text)
{
	_map_file_name = file_name_text;

	std::ifstream infile(file_name_text);
	std::string line = "";
	std::string word = "";

	std::getline(infile, line);
	std::istringstream iss(line);

	std::set<int> goal_door_ids = ReadContextFromFile(iss, word);

	float i = TILE_SIZE_HALF;
	int map_w = 0;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		float j = TILE_SIZE_HALF;
		int map_h = 0;
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
				MakeWall(i, j, map_w, map_h);
			}
			else if (object_type == SCENE_OBJECT_BOX)
			{
				MakeBox(i, j, map_w, map_h);
			}
			else if (object_type == SCENE_OBJECT_PRESSURE_PLATE)
			{
				MakePressurePlate(i, j);
			}
			else if (object_type == SCENE_OBJECT_DUNGEON_DOOR)
			{
				MakeDungeonDoor(i, j, word, goal_door_ids, token, map_w, map_h);
			}
			else if (object_type == SCENE_OBJECT_PATH)
			{
				MakePath(i, j, word, token, map_w, map_h);
			}
			else if (object_type == SCENE_OBJECT_GOAL_REWARD_TILE)
			{
				MakeGoalRewardsTile(i, j);
			}
			else if (object_type == SCENE_OBJECT_SLIME)
			{
				MakeSlime(i, j);
			}
			else if (object_type == SCENE_OBJECT_RESET_BUTTON)
			{
				MakeResetButton(i, j);
			}
			j += TILE_SIZE_FULL;
			++map_h;
		}
		i += TILE_SIZE_FULL;
		++map_w;
	}

	if (_goal_context == GOAL_CONTEXT_PRESSURE_PLATE)
	{
		StoreResetButtonData();
	}
}

void Scene::MakeFloor(float i, float j)
{
	const char* image_file = GenerateRandomBetween(0, 1) == 0 ? IMAGE_FLOOR : IMAGE_FLOOR_V2;

	std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>(image_file, 1, 1, i, j);
	std::shared_ptr<GameObject> floor =
		std::make_shared<GameObject>(renderer, i, j, TagType::STATIC_OBJECT);
	_scene_layers[LayerType::BACKGROUND].push_back(floor);
}

void Scene::MakeWall(float i, float j, int map_w, int map_h)
{
	const char* image_file = GenerateRandomBetween(0, 1) == 0 ? IMAGE_WALL : IMAGE_WALL_V2;

	std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>(image_file, 1, 1, i, j);
	std::shared_ptr<Actor> wall = std::make_shared<Actor>(renderer, i, j, TagType::STATIC_OBJECT);
	_scene_layers[LayerType::MIDDLEGROUND].push_back(wall);
	_map[map_w][map_h].push_back(wall);
}

void Scene::MakeBox(float i, float j, int map_w, int map_h)
{
	MakeFloor(i, j);

	std::shared_ptr<Renderer> box_renderer = std::make_shared<Renderer>(IMAGE_BOX, 1, 1, i, j);
	std::shared_ptr<Actor> box = std::make_shared<Actor>(box_renderer, i, j, TagType::MOVABLE_OBJECT);
	box->GetRenderer()->GetSprite()->SetScale(0.9f);
	_scene_layers[LayerType::FOREGROUND].push_back(box);
	_map[map_w][map_h].push_back(box);
}

void Scene::MakePressurePlate(float i, float j)
{
	MakeFloor(i, j);

	std::shared_ptr<Renderer> plate_renderer =
		std::make_shared<Renderer>(IMAGE_PRESSURE_PLATE, 1, 1, i, j);
	std::shared_ptr<PressurePlate> plate =
		std::make_shared<PressurePlate>(plate_renderer, i, j, TagType::PLATE);
	_scene_layers[LayerType::MIDDLEGROUND].push_back(plate);

	// TODO: CHANGE THIS TO GOAL TYPE MAPPING
	if (_goal_context == GOAL_CONTEXT_PRESSURE_PLATE)
	{
		_goal->IncrementContextCount();
	}
}

void Scene::MakeDungeonDoor(float i, float j, std::string& word, std::set<int> goal_door_ids, char* token, int map_w, int map_h)
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
		door_renderer = std::make_shared<Renderer>(IMAGE_DUNGEON_DOOR_LOCKED, 1, 1, i, j);
	}
	else if (type == DoorStateType::UNLOCKED)
	{
		door_renderer = std::make_shared<Renderer>(IMAGE_DUNGEON_DOOR_UNLOCKED, 1, 1, i, j);
	}

	std::unordered_map<char, char*>::iterator it = _map_id_mapping.find(_context_reading_order[LINKED_MAP_ID_INDEX]);
	char* linked_map = {};
	if (it != _map_id_mapping.end())
	{
		linked_map = it->second;
	}

	ItemType required_key_type = id == 0 ? ItemType::KEY_ESCAPE : ItemType::KEY;

	std::shared_ptr<DungeonDoor> door = 
		std::make_shared<DungeonDoor>(door_renderer, i, j, TagType::DOOR, type, id, linked_map, required_key_type);
	_scene_layers[LayerType::MIDDLEGROUND].push_back(door);
	_map[map_w][map_h].push_back(door);

	if (goal_door_ids.find(id) != goal_door_ids.end())
	{
		_goal_doors.push_back(door);
	}
}

void Scene::MakePath(float i, float j, std::string& word, char* token, int map_w, int map_h)
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
		std::make_shared<Renderer>(IMAGE_PATH, 1, 1, i, j);
	std::shared_ptr<Path> path =
		std::make_shared<Path>(path_renderer, i, j, TagType::DOOR, id, linked_map);
	_scene_layers[LayerType::MIDDLEGROUND].push_back(path);
	_map[map_w][map_h].push_back(path);
}

void Scene::MakeGoalRewardsTile(float i, float j)
{
	MakeFloor(i, j);

	std::shared_ptr<Renderer> renderer = std::make_shared<Renderer>(IMAGE_GOAL_REWARD_TILE, 1, 1, i, j);
	std::shared_ptr<GameObject> tile =
		std::make_shared<GameObject>(renderer, i, j, TagType::STATIC_OBJECT);
	_scene_layers[LayerType::BACKGROUND].push_back(tile);

	_goal->SetGoalRewardTile(tile.get());
}

void Scene::MakeKey(float i, float j)
{
	std::shared_ptr<Renderer> key_renderer = std::make_shared<Renderer>(IMAGE_KEY, 1, 1, i, j);
	std::shared_ptr<Key> key = std::make_shared<Key>(key_renderer, i, j, TagType::ITEM, ItemType::KEY);
	_scene_layers[LayerType::FOREGROUND].push_back(key);
}

void Scene::MakeKeyEscape(float i, float j)
{
	std::shared_ptr<Renderer> key_renderer = std::make_shared<Renderer>(IMAGE_KEY_ESCAPE, 1, 1, i, j);
	std::shared_ptr<Key> key = std::make_shared<Key>(key_renderer, i, j, TagType::ITEM, ItemType::KEY_ESCAPE);
	_scene_layers[LayerType::FOREGROUND].push_back(key);
}

void Scene::MakeSlime(float i, float j)
{
	MakeFloor(i, j);

	std::shared_ptr<Renderer> slime_renderer = std::make_shared<Renderer>(IMAGE_SLIME, 4, 4, i, j);
	std::shared_ptr<Slime> slime = std::make_shared<Slime>(slime_renderer, i, j, TagType::ENEMY, _player, this);
	slime->GetRenderer()->CreateSpriteAnimation(ANIMATION_SPEED, { 0, 1, 2, 3 }, { 4, 5, 6, 7 }, { 8, 9, 10, 11 }, { 12, 13, 14, 15 });
	slime->GetRenderer()->SetAnimation(FacingDirection::DOWN);
	_scene_layers[LayerType::CHARACTERS].push_back(slime);

	// TODO : MAKE THIS A COMPOSITE PATTERN?
	if (_goal_context == GOAL_CONTEXT_SLIME)
	{
		_goal->IncrementContextCount();
	}
}

void Scene::MakeResetButton(float i, float j)
{
	std::shared_ptr<Renderer> button_renderer = std::make_shared<Renderer>(IMAGE_RESET_BUTTON, 1, 1, i, j);
	std::shared_ptr<ResetButton> button = std::make_shared<ResetButton>(button_renderer, i, j, TagType::BUTTON);
	_scene_layers[LayerType::FOREGROUND].push_back(button);
}

void Scene::MakeFireball(float i, float j, FacingDirection direction)
{
	std::shared_ptr<Renderer> fireball_renderer = std::make_shared<Renderer>(IMAGE_FIREBALL, 1, 1, i, j);
	std::shared_ptr<Fireball> fireball = std::make_shared<Fireball>(fireball_renderer, i, j, TagType::SPELL, direction);

	_scene_layers[LayerType::SPELLS].push_back(fireball);
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
	int index_w = std::floor(position.X() / TILE_SIZE_FULL);
	int index_h = std::floor(position.Y() / TILE_SIZE_FULL);

	if (index_w < 0 || index_w >= MAP_WIDTH || index_h < 0 || index_h >= MAP_HEIGHT)
	{
		return false;
	}

	if (_map[index_w][index_h].size() > 0)
	{
		return false;
	}

	return true;
}

void Scene::MoveObjectPositionInMap(Vector2D& old_position, Vector2D& new_position, GameObject* object)
{
	// TODO : TEST

	int old_index_w = static_cast<int>(std::floor(old_position.X() / TILE_SIZE_FULL));
	int old_index_h = static_cast<int>(std::floor(old_position.Y() / TILE_SIZE_FULL));

	int new_index_w = static_cast<int>(std::floor(new_position.X() / TILE_SIZE_FULL));
	int new_index_h = static_cast<int>(std::floor(new_position.Y() / TILE_SIZE_FULL));

	if (old_index_w < 0 || old_index_w >= MAP_WIDTH || old_index_h < 0 || old_index_h >= MAP_HEIGHT ||
		new_index_w < 0 || new_index_w >= MAP_WIDTH || new_index_h < 0 || new_index_h >= MAP_HEIGHT)
	{
		return;
	}

	std::vector<std::shared_ptr<GameObject>> list = _map[old_index_w][old_index_h];
	std::vector<std::shared_ptr<GameObject>>::iterator it =
		std::find_if(list.begin(), list.end(), [object](const std::shared_ptr<GameObject>& o)
			{
				return (object->GetTag() == o->GetTag()) && (object->GetTransform()->X() == o->GetTransform()->X()) &&
					(object->GetTransform()->Y() == o->GetTransform()->Y());
			});
	if (it != list.end())
	{
		_map[old_index_w][old_index_h].erase(it);
	}

	_map[new_index_w][new_index_h].push_back(std::make_shared<GameObject>(*object));
}

void Scene::GetCoordinateByPosition(Vector2D& position, int& map_w, int& map_h)
{
	map_w = std::floor(position.X() / TILE_SIZE_FULL);
	map_h = std::floor(position.Y() / TILE_SIZE_FULL);
}

Vector2D Scene::GetPositionByCoordinate(int map_w, int map_h)
{
	float x = (static_cast<float>(map_w)) * TILE_SIZE_FULL + TILE_SIZE_HALF;
	float y = (static_cast<float>(map_h)) * TILE_SIZE_FULL + TILE_SIZE_HALF;

	return Vector2D(x, y);
}

void Scene::Update()
{
	if (_goal->IsGoalComplete())
	{
		for (std::shared_ptr<Door> door : _goal_doors)
		{
			// unlock all goal doors
			door->SetState(DoorStateType::UNLOCKED);
			_goal->SpawnReward(this);
		}
		if (_goal_context == GOAL_CONTEXT_PRESSURE_PLATE)
		{
			for (std::shared_ptr<GameObject> object : _scene_layers[LayerType::FOREGROUND])
			{
				if (object->GetTag() == TagType::BUTTON)
				{
					ResetButton& button = static_cast<ResetButton&>(*object.get());
					button.SetIsDisabled(true);
					break;
				}
			}
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

int Scene::GenerateRandomBetween(int min, int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distribution(min, max);

	return distribution(gen);
}

void Scene::StoreResetButtonData()
{
	for (std::shared_ptr<GameObject> object : _scene_layers[LayerType::FOREGROUND])
	{
		if (object->GetTag() == TagType::BUTTON)
		{
			ResetButton& button = static_cast<ResetButton&>(*object.get());
			button.SetOriginalGoalContextCount(_goal->GetContextCount());
			for (std::shared_ptr<GameObject> o : _scene_layers[LayerType::FOREGROUND])
			{
				// TODO : make tag box specific (only box is using it)
				if (o->GetTag() == TagType::MOVABLE_OBJECT)
				{
					button.AddToOriginalBoxLocation(*o->GetTransform().get());
				}
			}
			break;
		}
	}
}


