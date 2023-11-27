#include "stdafx.h"
#include "Scene.h"
#include "Renderer.h"

void Scene::LoadMap(const char* file_name_text, std::vector<std::shared_ptr<Actor>>& actors, std::vector<std::shared_ptr<GameObject>>& game_objects)
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
				game_objects.push_back(floor);
			}
			else if (scene_obj_type == SceneObjectType::WALL)
			{
				std::shared_ptr<Renderer> renderer(new Renderer(".\\Images\\WallL.bmp", 1, 1, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF));
				std::shared_ptr<Actor> wall(new Actor(renderer, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF, TagType::STATIC_OBJECT));
				actors.push_back(wall);
			}
			else if (scene_obj_type == SceneObjectType::BOX)
			{
				std::shared_ptr<Renderer> floor_renderer(new Renderer(".\\Images\\FloorL.bmp", 1, 1, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF));
				std::shared_ptr<GameObject> floor(new GameObject(floor_renderer, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF, TagType::STATIC_OBJECT));
				game_objects.push_back(floor);

				std::shared_ptr<Renderer> box_renderer(new Renderer(".\\Images\\BoxL.bmp", 1, 1, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF));
				std::shared_ptr<Actor> box(new Actor(box_renderer, i + IMAGE_SIZE_HALF, j + IMAGE_SIZE_HALF, TagType::MOVABLE_OBJECT));
				actors.push_back(box);
			}
			j += MOVABLE_OBJECT_MOVE_BY;
		}
		i += MOVABLE_OBJECT_MOVE_BY;
	}
}
