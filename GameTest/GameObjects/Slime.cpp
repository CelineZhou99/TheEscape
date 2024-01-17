#include "stdafx.h"
#include "Slime.h"
#include "../BehaviourTree/Blackboard.h"

void Slime::BehaviourTreeInit(Player* player, Scene* scene)
{
	_behaviour_tree = std::make_shared<BehaviourTree>(RootNodeType::SELECTOR);
	_behaviour_tree->AddActionNode(_behaviour_tree->GetRoot(), std::bind(&Slime::MoveTo, this));
	_behaviour_tree->AddActionNode(_behaviour_tree->GetRoot(), std::bind(&Slime::SetMoveToLocation, this, scene));
	//_behaviour_tree->AddActionNode(_behaviour_tree->GetRoot(), std::bind(&Slime::SayHello, this));
	//_behaviour_tree->AddActionNode(_behaviour_tree->GetRoot(), std::bind(&Slime::SayBye, this));
}

BehaviourNodeState Slime::MoveTo()
{
	// TODO : ASK ABOUT TEMPLATE TYPE AND CASTING
	/*any_type location = _behaviour_tree->GetBlackboard()->GetVariable(MOVE_TO_LOCATION);
	Vector2D value = dynamic_cast<Any<Vector2D>&>(*(location.get())).GetData();*/
	std::shared_ptr<Vector2D> location = _behaviour_tree->GetBlackboard()->GetVectorVariable(MOVE_TO_LOCATION);
	FacingDirection direction = _behaviour_tree->GetBlackboard()->GetDirectionVariable(MOVE_TO_DIRECTION);

	std::wstringstream wss;
	wss << L" MOVING \n";
	OutputDebugString(wss.str().c_str());
	if (location && direction != FacingDirection::NONE)
	{
		switch (direction)
		{
		case FacingDirection::UP:
			UpdatePosition(0, 1, direction);
			break;
		case FacingDirection::DOWN:
			UpdatePosition(0, -1, direction);
			break;
		case FacingDirection::LEFT:
			UpdatePosition(-1, 0, direction);
			break;
		case FacingDirection::RIGHT:
			UpdatePosition(1, 0, direction);
			break;
		}
		wss << L" transform x " << _transform->X() << "location x " << location->X() << "\n";
		OutputDebugString(wss.str().c_str());
		wss << L" transform y " << _transform->Y() << "location y " << location->Y() << "\n";
		OutputDebugString(wss.str().c_str());
		if (_transform->X() == location->X() && _transform->Y() == location->Y())
		{
			_behaviour_tree->GetBlackboard()->RemoveVectorVariable(MOVE_TO_LOCATION);
			_behaviour_tree->GetBlackboard()->RemoveDirectionVariable(MOVE_TO_DIRECTION);
			return BehaviourNodeState::SUCCESS;
		}
		return BehaviourNodeState::RUNNING;
	}
	else
	{
		return BehaviourNodeState::FAILED;
	}
	
}

BehaviourNodeState Slime::MoveToPlayer(Player* player)
{
	return BehaviourNodeState::SUCCESS;
}

BehaviourNodeState Slime::SetMoveToLocation(Scene* scene)
{
	Vector2D top = Vector2D(_transform->X(), _transform->Y() + TILE_SIZE_FULL);
	Vector2D down = Vector2D(_transform->X(), _transform->Y() - TILE_SIZE_FULL);
	Vector2D left = Vector2D(_transform->X() - TILE_SIZE_FULL, _transform->Y());
	Vector2D right = Vector2D(_transform->X() + TILE_SIZE_FULL, _transform->Y());

	std::vector<Vector2D> free_directions = {};
	std::vector<FacingDirection> directions = {};

	if (scene->IsSpaceFree(top))
	{
		free_directions.push_back(top);
		directions.push_back(FacingDirection::UP);
	}
	if (scene->IsSpaceFree(down))
	{
		free_directions.push_back(down);
		directions.push_back(FacingDirection::DOWN);
	}
	if (scene->IsSpaceFree(left))
	{
		free_directions.push_back(left);
		directions.push_back(FacingDirection::LEFT);
	}
	if (scene->IsSpaceFree(right))
	{
		free_directions.push_back(right);
		directions.push_back(FacingDirection::RIGHT);
	}
	
	if (free_directions.size() <= 0)
	{
		return BehaviourNodeState::FAILED;
	}

	int random_index = scene->GenerateRandomBetween(0, free_directions.size() - 1);
	_behaviour_tree->GetBlackboard()->SetVariable(MOVE_TO_LOCATION, Any<Vector2D>(free_directions[random_index]));

	// temp
	_behaviour_tree->GetBlackboard()->SetVectorVariable(MOVE_TO_LOCATION, free_directions[random_index]);
	_behaviour_tree->GetBlackboard()->SetDirectionVariable(MOVE_TO_DIRECTION, directions[random_index]);

	float x = free_directions[random_index].X();
	float y = free_directions[random_index].Y();
	std::wstringstream wss;
	wss << L" SET LOCATION SUCCESS " << x << " " << y << "\n";
	OutputDebugString(wss.str().c_str());
	return BehaviourNodeState::SUCCESS;
}

// TODO: 
// temp to avoid circular dependency between slime and slime controller
void Slime::UpdatePosition(float move_by_x, float move_by_y, FacingDirection direction)
{
	GetTransform()->MoveVectorPosition(move_by_x, move_by_y);
	GetRenderer()->SetAnimationWithMovement(direction);
	GetCollider()->MoveColliderPosition(move_by_x, move_by_y);
}
