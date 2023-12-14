#pragma once
#include <math.h>  
#include "../GameObjects/Actor.h"
#include "../Observers/Subscriber.h"
#include "../Observers/Goal.h"
#include "../GameObjects/Door.h"

enum SceneObjectType
{
	FLOOR,
	WALL,
	BOX,
	PRESSURE_PLATE,
	DOOR_INVISIBLE,
	DOOR_UNLOCKED,
	DOOR_LOCKED
};
class Scene : public Subscriber
{
public:
	Scene(Goal* goal) : _goal(goal) {}

	// TODO: 
	// have a grid representation of the objects in the scene e.g. 2d array
	// // then can use that to check if some objects are overlapping (could be useful) 
	void LoadMap(const char* file_name_text);

	std::vector<std::shared_ptr<GameObject>> GetBackgroundObjects() { return _background_objects; }
	std::vector<std::shared_ptr<Actor>> GetMiddlegroundObjects() { return _middleground_objects; }
	std::vector<std::shared_ptr<Actor>> GetForegroundObjects() { return _foreground_objects; }

	void Update() override;


private:
	std::vector<std::shared_ptr<GameObject>> _background_objects = {};
	std::vector<std::shared_ptr<Actor>> _middleground_objects = {};
	std::vector<std::shared_ptr<Actor>> _foreground_objects = {};

	std::vector<std::shared_ptr<Door>> _goal_doors = {};

	Goal* _goal;

};

