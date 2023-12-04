#pragma once
#include <math.h>  
#include "Actor.h"

enum SceneObjectType
{
	FLOOR,
	WALL,
	BOX,
	PRESSURE_PLATE,
	DOOR
};
class Scene
{
public:
	void LoadMap(const char* file_name_text, std::vector<std::shared_ptr<GameObject>>& background_objects, 
		std::vector<std::shared_ptr<Actor>>& middleground_objects, std::vector<std::shared_ptr<Actor>>& foreground_objects);
};

