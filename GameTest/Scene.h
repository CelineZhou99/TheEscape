#pragma once
#include <math.h>  
#include "Actor.h"

enum SceneObjectType
{
	FLOOR,
	WALL,
	BOX
};
class Scene
{
public:
	void LoadMap(const char* file_name_text, std::vector<std::shared_ptr<Actor>>& actors, std::vector<std::shared_ptr<GameObject>>& game_objects);
};

