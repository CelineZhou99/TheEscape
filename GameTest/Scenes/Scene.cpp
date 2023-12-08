#include "stdafx.h"
#include "Scene.h"
#include "../GameObjects/Renderer.h"
#include "../GameObjects/InvisibleDoor.h"
#include "../GameObjects/DungeonDoor.h"
#include "../PressurePlate.h"

void Scene::LoadMap(const char* file_name_text)
{
	std::ifstream infile(file_name_text);
	std::string line;
	float i = 0;
	int scene_obj_type = 0;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		float j = 0;
		while (iss >> scene_obj_type)
		{
			if (scene_obj_type == SceneObjectType::FLOOR)
			{
				std::shared_ptr<Renderer> renderer(new Renderer(".\\Images\\FloorL.bmp", 1, 1, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF));
				std::shared_ptr<GameObject> floor(new GameObject(renderer, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF, TagType::STATIC_OBJECT));
				_background_objects.push_back(floor);
			}
			else if (scene_obj_type == SceneObjectType::WALL)
			{
				std::shared_ptr<Renderer> renderer(new Renderer(".\\Images\\WallL.bmp", 1, 1, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF));
				std::shared_ptr<Actor> wall(new Actor(renderer, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF, TagType::STATIC_OBJECT));
				_middleground_objects.push_back(wall);
			}
			else if (scene_obj_type == SceneObjectType::BOX)
			{
				std::shared_ptr<Renderer> floor_renderer(new Renderer(".\\Images\\FloorL.bmp", 1, 1, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF));
				std::shared_ptr<GameObject> floor(new GameObject(floor_renderer, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF, TagType::STATIC_OBJECT));
				_background_objects.push_back(floor);

				std::shared_ptr<Renderer> box_renderer(new Renderer(".\\Images\\BoxL.bmp", 1, 1, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF));
				std::shared_ptr<Actor> box(new Actor(box_renderer, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF, TagType::MOVABLE_OBJECT));
				box->GetRenderer()->GetSprite()->SetScale(0.9f);
				_foreground_objects.push_back(box);
			}
			else if (scene_obj_type == SceneObjectType::PRESSURE_PLATE)
			{
				std::shared_ptr<Renderer> floor_renderer(new Renderer(".\\Images\\FloorL.bmp", 1, 1, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF));
				std::shared_ptr<GameObject> floor(new GameObject(floor_renderer, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF, TagType::STATIC_OBJECT));
				_background_objects.push_back(floor);

				std::shared_ptr<Renderer> plate_renderer(new Renderer(".\\Images\\PressurePlateL.bmp", 1, 1, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF));
				std::shared_ptr<PressurePlate> plate(new PressurePlate(plate_renderer, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF, TagType::PLATE));
				_middleground_objects.push_back(plate);

				// TODO: find a way to not hardcode incrementing the goal context
				_goal->IncrementContextCount();
			}
			else if (scene_obj_type == SceneObjectType::DOOR_INVISIBLE)
			{
				std::shared_ptr<Renderer> floor_renderer(new Renderer(".\\Images\\FloorL.bmp", 1, 1, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF));
				std::shared_ptr<GameObject> floor(new GameObject(floor_renderer, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF, TagType::STATIC_OBJECT));
				_background_objects.push_back(floor);

				std::shared_ptr<Renderer> door_renderer(new Renderer(".\\Images\\InvisibleDoor.bmp", 1, 1, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF));
				std::shared_ptr<InvisibleDoor> door(new InvisibleDoor(door_renderer, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF, TagType::DOOR, DoorStateType::UNLOCKED));
				_middleground_objects.push_back(door);
			}
			else if (scene_obj_type == SceneObjectType::DOOR_LOCKED)
			{
				std::shared_ptr<Renderer> floor_renderer(new Renderer(".\\Images\\FloorL.bmp", 1, 1, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF));
				std::shared_ptr<GameObject> floor(new GameObject(floor_renderer, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF, TagType::STATIC_OBJECT));
				_background_objects.push_back(floor);

				std::shared_ptr<Renderer> door_renderer(new Renderer(".\\Images\\DungeonDoorLocked.bmp", 1, 1, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF));
				std::shared_ptr<DungeonDoor> door(new DungeonDoor(door_renderer, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF, TagType::DOOR, DoorStateType::LOCKED));
				_middleground_objects.push_back(door);

				// TODO: find a way to identify if a door is part of a goal or not, for now is hardcoded
				_goal_doors.push_back(door);
			}
			else if (scene_obj_type == SceneObjectType::DOOR_UNLOCKED)
			{
				std::shared_ptr<Renderer> floor_renderer(new Renderer(".\\Images\\FloorL.bmp", 1, 1, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF));
				std::shared_ptr<GameObject> floor(new GameObject(floor_renderer, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF, TagType::STATIC_OBJECT));
				_background_objects.push_back(floor);

				std::shared_ptr<Renderer> door_renderer(new Renderer(".\\Images\\DungeonDoorUnlocked.bmp", 1, 1, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF));
				std::shared_ptr<DungeonDoor> door(new DungeonDoor(door_renderer, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF, TagType::DOOR, DoorStateType::UNLOCKED));
				_middleground_objects.push_back(door);
			}
			j += MOVABLE_OBJECT_MOVE_BY;
		}
		i += MOVABLE_OBJECT_MOVE_BY;
	}
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


