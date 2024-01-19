#include "stdafx.h"
#include "Slime.h"
#include "../BehaviourTree/Blackboard.h"

void Slime::BehaviourTreeInit(Player* player, Scene* scene)
{
	_behaviour_tree = std::make_shared<BehaviourTree>(RootNodeType::SELECTOR);
	_behaviour_tree->AddActionNode(_behaviour_tree->GetRoot(), std::bind(&Slime::MoveTo, this, scene));
	_behaviour_tree->AddActionNode(_behaviour_tree->GetRoot(), std::bind(&Slime::SetMoveToLocation, this, scene));
}

BehaviourNodeState Slime::MoveTo(Scene* scene)
{
	// TODO : ASK ABOUT TEMPLATE TYPE AND CASTING
	any_type_ptr location_ptr = _behaviour_tree->GetBlackboard()->GetVariable(MOVE_TO_LOCATION);
	any_type_ptr direction_ptr = _behaviour_tree->GetBlackboard()->GetVariable(MOVE_TO_DIRECTION);

	Vector2D location = Vector2D();
	FacingDirection direction = FacingDirection::NONE;

	if (!location_ptr || !direction_ptr)
	{
		return BehaviourNodeState::FAILED;
	}
	
	location = static_cast<Any<Vector2D>*>(location_ptr.get())->GetData();
	direction = static_cast<Any<FacingDirection>*>(direction_ptr.get())->GetData();

	float x, y = 0;
	switch (direction)
	{
	case FacingDirection::UP:
		x = 0;
		y = 1;
		break;
	case FacingDirection::DOWN:
		x = 0;
		y = -1;
		break;
	case FacingDirection::LEFT:
		x = -1;
		y = 0;
		break;
	case FacingDirection::RIGHT:
		x = 1;
		y = 0;
		break;
	case FacingDirection::NONE:
		return BehaviourNodeState::FAILED;
	}

	BoxCollider collider(*this->GetCollider());
	collider.MoveColliderPosition(x, y);
	object_list characters = scene->GetSceneLayers().at(LayerType::CHARACTERS);
	for (std::shared_ptr<GameObject> object : characters)
	{
		if (object.get() == this)
		{
			continue;
		}
		// if the slime will collide with another character, return failed and get a new location
		Actor& actor = static_cast<Actor&>(*object.get());
		if (GetCollider()->CheckCollision(collider, *actor.GetCollider()))
		{
			/*if (actor.GetTag() == TagType::ENEMY)
			{
				return BehaviourNodeState::FAILED;
			}*/
			return BehaviourNodeState::FAILED;
		}
	}

	UpdatePosition(x, y, direction);

	if (_transform->X() == location.X() && _transform->Y() == location.Y())
	{
		_behaviour_tree->GetBlackboard()->RemoveVariable(MOVE_TO_LOCATION);
		_behaviour_tree->GetBlackboard()->RemoveVariable(MOVE_TO_DIRECTION);

		return BehaviourNodeState::SUCCESS;
	}
	return BehaviourNodeState::RUNNING;
	
}

BehaviourNodeState Slime::MoveToPlayer(Player* player)
{
	return BehaviourNodeState::SUCCESS;
}

BehaviourNodeState Slime::SetMoveToLocation(Scene* scene)
{
	int map_w = 0;
	int map_h = 0;
	scene->GetCoordinateByPosition(*_transform.get(), map_w, map_h);
	
	Vector2D top = scene->GetPositionByCoordinate(map_w, map_h + 1);
	Vector2D down = scene->GetPositionByCoordinate(map_w, map_h - 1);
	Vector2D left = scene->GetPositionByCoordinate(map_w - 1, map_h);
	Vector2D right = scene->GetPositionByCoordinate(map_w + 1, map_h);

	std::vector<Vector2D> free_locations = {};
	std::vector<FacingDirection> free_directions = {};

	// enemy needs to be directly to the top/down/left/right of the space for it to be free
	if (scene->IsSpaceFree(top))
	{
		if (_transform->X() == top.X())
		{
			free_locations.push_back(top);
			free_directions.push_back(FacingDirection::UP);
		}
	}
	if (scene->IsSpaceFree(down))
	{
		if (_transform->X() == down.X())
		{
			free_locations.push_back(down);
			free_directions.push_back(FacingDirection::DOWN);
		}
	}
	if (scene->IsSpaceFree(left))
	{
		if (_transform->Y() == left.Y())
		{
			free_locations.push_back(left);
			free_directions.push_back(FacingDirection::LEFT);
		}
	}
	if (scene->IsSpaceFree(right))
	{
		if (_transform->Y() == right.Y())
		{
			free_locations.push_back(right);
			free_directions.push_back(FacingDirection::RIGHT);
		}
	}
	
	if (free_locations.size() <= 0)
	{
		return BehaviourNodeState::FAILED;
	}

	int random_index = scene->GenerateRandomBetween(0, free_locations.size() - 1);
	_behaviour_tree->GetBlackboard()->SetVariable(MOVE_TO_LOCATION, new Any<Vector2D>(free_locations[random_index]));
	_behaviour_tree->GetBlackboard()->SetVariable(MOVE_TO_DIRECTION, new Any<FacingDirection>(free_directions[random_index]));

	return BehaviourNodeState::SUCCESS;
}

// TODO: 
// temp to avoid circular dependency between slime and slime controller
void Slime::UpdatePosition(float move_by_x, float move_by_y, FacingDirection direction)
{
	GetTransform()->MoveVectorPosition(move_by_x, move_by_y);
	GetRenderer()->SetAnimationWithMovement(direction, move_by_x, move_by_y);
	GetCollider()->MoveColliderPosition(move_by_x, move_by_y);
}
