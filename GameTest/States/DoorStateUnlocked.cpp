#include "stdafx.h"
#include "DoorStateUnlocked.h"
#include "../World.h"

void DoorStateUnlocked::SetSpriteImage()
{
	float x, y = 0;
	_door->GetRenderer()->GetSprite()->GetPosition(x, y);
	// TODO : PUT STRING INTO A MAP
	_door->GetRenderer()->SetSprite(IMAGE_DUNGEON_DOOR_UNLOCKED, 1, 1);
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
		world.current_scene->AddToSceneLayers(world.player, LayerType::CHARACTERS);
		world.current_scene->LoadMap(_door->GetLinkedMap());
		world.current_goal->SetGoalType(world.current_scene->GetGoalType());
		world.current_goal->Subscribe(world.current_scene.get());

		std::shared_ptr<Actor> new_door = world.current_scene->GetDoorWithId(door_id);

		if (new_door)
		{
			// check all 4 directions of new door to find a space to spawn player
			int map_w = 0;
			int map_h = 0;
			world.current_scene->GetCoordinateByPosition(*new_door->GetTransform(), map_w, map_h);

			Vector2D top = world.current_scene->GetPositionByCoordinate(map_w, map_h + 1);
			Vector2D down = world.current_scene->GetPositionByCoordinate(map_w, map_h - 1);
			Vector2D left = world.current_scene->GetPositionByCoordinate(map_w - 1, map_h);
			Vector2D right = world.current_scene->GetPositionByCoordinate(map_w + 1, map_h);

			if (world.current_scene->IsSpaceFree(top))
			{
				world.player_controller->SetControlledActorPosition(top.X(), top.Y() + TILE_SIZE_HALF, FacingDirection::UP);
				return;
			}
			if (world.current_scene->IsSpaceFree(down))
			{
				world.player_controller->SetControlledActorPosition(down.X(), down.Y() - TILE_SIZE_HALF, FacingDirection::DOWN);
				return;
			}
			if (world.current_scene->IsSpaceFree(left))
			{
				world.player_controller->SetControlledActorPosition(left.X() - TILE_SIZE_HALF, left.Y(), FacingDirection::LEFT);
				return;
			}
			if (world.current_scene->IsSpaceFree(right))
			{
				world.player_controller->SetControlledActorPosition(right.X() + TILE_SIZE_HALF, right.Y(), FacingDirection::RIGHT);
				return;
			}
		}
	}
	else
	{
		world.GameEndEscaped();
	}

}
