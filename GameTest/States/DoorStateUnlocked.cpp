#include "stdafx.h"
#include "../GameObjects/Door.h"
#include "DoorStateUnlocked.h"
#include "../World.h"

void DoorStateUnlocked::SetSpriteImage()
{
	float x, y = 0;
	_door->GetRenderer()->GetSprite()->GetPosition(x, y);
	_door->GetRenderer()->SetSprite(".\\Data\\Images\\DungeonDoorUnlocked.bmp", 1, 1);
	_door->GetRenderer()->GetSprite()->SetPosition(x, y);
}

void DoorStateUnlocked::OnCollideWithPlayer(World& world)
{
	// let player through
	int door_id = _door->GetId();

	std::shared_ptr<Goal> new_goal = std::make_shared<Goal>();
	world.current_goal = new_goal;

	world.current_scene.reset();
	world.current_scene = std::make_unique<Scene>(world.current_goal.get());

	if (_door->GetLinkedMap())
	{
		world.current_scene->LoadMap(_door->GetLinkedMap());
		world.current_goal->SetGoalType(world.current_scene->GetGoalType());
		world.current_goal->Subscribe(world.current_scene.get());
		world.current_scene->AddToSceneLayers(world.player, LayerType::CHARACTERS);

		std::shared_ptr<Actor> new_door = world.current_scene->GetDoorWithId(door_id);

		if (new_door)
		{
			std::shared_ptr<Vector2D> player_transform = world.player->GetTransform();
			// check all 4 directions of new door to find a space to spawn player
			std::shared_ptr<Vector2D> transform = new_door->GetTransform();
			std::shared_ptr<Vector2D> top = std::make_shared<Vector2D>(transform->X(), transform->Y() + IMAGE_SIZE_FULL);
			std::shared_ptr<Vector2D> down = std::make_shared<Vector2D>(transform->X(), transform->Y() - IMAGE_SIZE_FULL);
			std::shared_ptr<Vector2D> left = std::make_shared<Vector2D>(transform->X() - IMAGE_SIZE_FULL, transform->Y());
			std::shared_ptr<Vector2D> right = std::make_shared<Vector2D>(transform->X() + IMAGE_SIZE_FULL, transform->Y());

			if (top->X() >= 0 && top->Y() >= 0 && top->X() <= APP_VIRTUAL_WIDTH && top->Y() <= APP_VIRTUAL_HEIGHT)
			{
				if (world.current_scene->IsSpaceFree(*top))
				{
					world.player_controller->SetPlayerPosition(top->X(), top->Y() + 32, FacingDirection::UP);
					return;
				}
			}
			if (down->X() >= 0 && down->Y() >= 0 && down->X() <= APP_VIRTUAL_WIDTH && down->Y() <= APP_VIRTUAL_HEIGHT)
			{
				if (world.current_scene->IsSpaceFree(*down))
				{
					world.player_controller->SetPlayerPosition(down->X(), down->Y() - 32, FacingDirection::DOWN);
					return;
				}
			}
			if (left->X() >= 0 && left->Y() >= 0 && left->X() <= APP_VIRTUAL_WIDTH && left->Y() <= APP_VIRTUAL_HEIGHT)
			{
				if (world.current_scene->IsSpaceFree(*left))
				{
					world.player_controller->SetPlayerPosition(left->X() - 32, left->Y(), FacingDirection::LEFT);
					return;
				}
			}
			if (right->X() >= 0 && right->Y() >= 0 && right->X() <= APP_VIRTUAL_WIDTH && right->Y() <= APP_VIRTUAL_HEIGHT)
			{
				if (world.current_scene->IsSpaceFree(*right))
				{
					world.player_controller->SetPlayerPosition(right->X() + 32, right->Y(), FacingDirection::RIGHT);
					return;
				}
			}
		}
	}
	else
	{
		world.GameEnd();
	}

}
