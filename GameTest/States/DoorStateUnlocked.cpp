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
			// check all 4 directions of new door to find a space to spawn player
			Vector2D* transform = new_door->GetTransform().get();
			Vector2D top = Vector2D(transform->X(), transform->Y() + TILE_SIZE_FULL);
			Vector2D down = Vector2D(transform->X(), transform->Y() - TILE_SIZE_FULL);
			Vector2D left = Vector2D(transform->X() - TILE_SIZE_FULL, transform->Y());
			Vector2D right = Vector2D(transform->X() + TILE_SIZE_FULL, transform->Y());

			if (world.current_scene->IsSpaceFree(top))
			{
				world.player_controller->SetControlledActorPosition(top.X(), top.Y() + 32, FacingDirection::UP);
				return;
			}
			if (world.current_scene->IsSpaceFree(down))
			{
				world.player_controller->SetControlledActorPosition(down.X(), down.Y() - 32, FacingDirection::DOWN);
				return;
			}
			if (world.current_scene->IsSpaceFree(left))
			{
				world.player_controller->SetControlledActorPosition(left.X() - 32, left.Y(), FacingDirection::LEFT);
				return;
			}
			if (world.current_scene->IsSpaceFree(right))
			{
				world.player_controller->SetControlledActorPosition(right.X() + 32, right.Y(), FacingDirection::RIGHT);
				return;
			}
		}
	}
	else
	{
		world.GameEnd();
	}

}
