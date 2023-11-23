#include "stdafx.h"
#include "Scene.h"
#include "Renderer.h"

void Scene::LoadMap(const char* file_name_text, std::vector<Actor*>* actors, std::vector<GameObject*>* game_objects)
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
			std::wstringstream wss;
			wss << L" " << scene_obj_type << "\n";
			OutputDebugString(wss.str().c_str());
			if (scene_obj_type == SceneObjectType::FLOOR)
			{
				Renderer* renderer = new Renderer(".\\Images\\FloorL.bmp", 1, 1, i + 32, j + 32);
				GameObject* floor = new GameObject(renderer, i + 32, j + 32, TagType::STATIC_OBJECT);
				game_objects->push_back(floor);
			}
			else if (scene_obj_type == SceneObjectType::WALL)
			{
				Renderer* renderer = new Renderer(".\\Images\\WallL.bmp", 1, 1, i + 32, j + 32);
				Actor* wall = new Actor(renderer, i + 32, j + 32, TagType::STATIC_OBJECT);
				actors->push_back(wall);
			}
			else if (scene_obj_type == SceneObjectType::BOX)
			{
				Renderer* floor_renderer = new Renderer(".\\Images\\FloorL.bmp", 1, 1, i + 32, j + 32);
				GameObject* floor = new GameObject(floor_renderer, i + 32, j + 32, TagType::STATIC_OBJECT);
				game_objects->push_back(floor);

				Renderer* box_renderer = new Renderer(".\\Images\\BoxL.bmp", 1, 1, i + 32, j + 32);
				Actor* box = new Actor(box_renderer, i + 32, j + 32, TagType::MOVABLE_OBJECT);
				actors->push_back(box);
			}
			j += 64;
		}
		i += 64;
	}
	

}
