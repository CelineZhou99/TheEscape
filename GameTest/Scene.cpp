#include "stdafx.h"
#include "Scene.h"

void Scene::InitialiseScene(const char* file_name_text, const char* file_name_image, std::vector<SquareActor*>* square_actors)
{
	std::ifstream infile(file_name_text);
	float x, y;
	while (infile >> x >> y)
	{
		SquareActor* actor = new SquareActor(file_name_image, 1, 1, x, y, TagType::STATIC_OBJECT);
		square_actors->push_back(actor);
	}
}
