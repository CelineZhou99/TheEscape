#pragma once
#include <math.h>  
#include "SquareActor.h"

class Scene
{
public:
	void InitialiseScene(const char* file_name_text, const char* file_name_image, std::vector<SquareActor*>* square_actors);
};

