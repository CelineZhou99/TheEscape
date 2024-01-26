#include "stdafx.h"
#include "Slime.h"
#include "../BehaviourTree/Blackboard.h"
#include "../BehaviourTree/DecoratorNode.h"
#include "../Scenes/Scene.h"
#include "../GameObjects/Player.h"
#include "../BehaviourTree/SetPlayerInRangeService.h"

void Slime::BehaviourTreeInit(Scene* scene)
{
	Player* player = nullptr;
	ObjectsList character_list = scene->GetSceneLayers().at(LayerType::CHARACTERS);

	for (GameObjectPtr character : character_list)
	{
		if (character->GetTag() == TagType::PLAYER)
		{
			player = static_cast<Player*>(character.get());
			break;
		}
	}

	_behaviour_tree = std::make_shared<BehaviourTree>(RootNodeType::SEQUENCE);

	node_ptr service = std::make_shared<SetPlayerInRangeService>(_behaviour_tree->AllocateId(), player, this, scene, _behaviour_tree->GetBlackboard().get());
	_behaviour_tree->GetRoot()->SetService(service);

	_behaviour_tree->AddActionNode(_behaviour_tree->GetRoot(), std::bind(&Slime::ChangeColour, this));

	node_ptr selector = _behaviour_tree->AddSelectorNode(_behaviour_tree->GetRoot());

	std::vector<std::string> decorator_variable_list = { BLACKBOARD_MOVE_TO_LOCATION, BLACKBOARD_MOVE_TO_DIRECTION };
	node_ptr decorator = _behaviour_tree->AddDecoratorNode(selector,
		decorator_variable_list, _behaviour_tree->GetBlackboard().get());

	_behaviour_tree->AddActionNode(decorator, std::bind(&Slime::MoveTo, this, scene));
	_behaviour_tree->AddActionNode(selector, std::bind(&Slime::SetMoveToLocation, this, scene));
}

BehaviourNodeState Slime::MoveTo(Scene* scene)
{
	any_type_ptr location_ptr = _behaviour_tree->GetBlackboard()->GetVariable(BLACKBOARD_MOVE_TO_LOCATION);
	any_type_ptr direction_ptr = _behaviour_tree->GetBlackboard()->GetVariable(BLACKBOARD_MOVE_TO_DIRECTION);

	Vector2D location = static_cast<Any<Vector2D>*>(location_ptr.get())->GetData();
	FacingDirection direction = static_cast<Any<FacingDirection>*>(direction_ptr.get())->GetData();

	float x, y = 0;
	switch (direction)
	{
	case FacingDirection::UP:
		x = 0;
		y = GetSpeed();
		break;
	case FacingDirection::DOWN:
		x = 0;
		y = -GetSpeed();
		break;
	case FacingDirection::LEFT:
		x = -GetSpeed();
		y = 0;
		break;
	case FacingDirection::RIGHT:
		x = GetSpeed();
		y = 0;
		break;
	case FacingDirection::NONE:
		return BehaviourNodeState::FAILED;
	}

	BoxCollider collider(*this->GetCollider());
	collider.MoveColliderPosition(x, y);
	ObjectsList characters = scene->GetSceneLayers().at(LayerType::CHARACTERS);
	for (GameObjectPtr object : characters)
	{
		if (object.get() == this)
		{
			continue;
		}
		// if the slime will collide with another character, return failed and get a new location
		Actor& actor = static_cast<Actor&>(*object.get());
		if (GetCollider()->CheckCollision(collider, *actor.GetCollider()))
		{
			if (actor.GetTag() == TagType::PLAYER)
			{
				Player& player = static_cast<Player&>(actor);
				player.TakeDamage();
			}
			return BehaviourNodeState::FAILED;
		}
	}

	UpdateAnimatedActorPosition(x, y, direction);

	if (_transform->X() == location.X() && _transform->Y() == location.Y())
	{
		_behaviour_tree->GetBlackboard()->RemoveVariable(BLACKBOARD_MOVE_TO_LOCATION);
		_behaviour_tree->GetBlackboard()->RemoveVariable(BLACKBOARD_MOVE_TO_DIRECTION);

		return BehaviourNodeState::SUCCESS;
	}
	return BehaviourNodeState::RUNNING;
}

BehaviourNodeState Slime::ChangeColour()
{
	any_type_ptr player_ptr = _behaviour_tree->GetBlackboard()->GetVariable(BLACKBOARD_PLAYER);

	if (player_ptr)
	{
		_renderer->GetSprite()->SetColor(1.0f, 0.f, 0.32f);
	}
	else
	{
		_renderer->GetSprite()->SetColor(1, 1, 1);
	}

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

	int random_index = scene->GenerateRandomBetween(0, static_cast<int>(free_locations.size() - 1));
	_behaviour_tree->GetBlackboard()->SetVariable(BLACKBOARD_MOVE_TO_LOCATION, new Any<Vector2D>(free_locations[random_index]));
	_behaviour_tree->GetBlackboard()->SetVariable(BLACKBOARD_MOVE_TO_DIRECTION, new Any<FacingDirection>(free_directions[random_index]));

	return BehaviourNodeState::SUCCESS;
}

void Slime::OnDeath(Scene* scene, LayerType layer)
{
	Actor::OnDeath(scene, layer);

	if (scene->GetGoalType() == GoalType::GOAL_SLIME)
	{
		scene->GetGoal()->DecrementContextCount();
		scene->GetGoal()->NotifySubscribers();
	}
}

void Slime::Update(float deltaTime, Scene* scene)
{
	Actor::Update(deltaTime, scene);

	_behaviour_tree->Update();
}
