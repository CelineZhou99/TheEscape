#include "stdafx.h"
#include "DoorStateUnlocked.h"
#include "../World.h"

void DoorStateUnlocked::SetSpriteImage()
{
	float x, y = 0;
	_door->GetRenderer()->GetSprite()->GetPosition(x, y);
	_door->GetRenderer()->SetSprite(IMAGE_DUNGEON_DOOR_UNLOCKED, 1, 1);
	_door->GetRenderer()->GetSprite()->SetPosition(x, y);
}

void DoorStateUnlocked::OnCollideWithPlayer(World& world)
{
	// let player through
	int door_id = _door->GetDoorId();

	std::shared_ptr<Goal> new_goal = std::make_shared<Goal>(world);
	world.SetCurrGoal(new_goal);

	world.ResetScene();
	world.SetCurrScene();

	if (_door->GetLinkedMap())
	{
		world.GetCurrScene()->AddToSceneLayers(world.GetPlayer(), LayerType::CHARACTERS);
		world.GetCurrScene()->LoadMap(_door->GetLinkedMap());
		world.GetCurrGoal()->SetGoalType(world.GetCurrScene()->GetGoalType());
		world.GetCurrGoal()->Subscribe(world.GetCurrScene());

		std::shared_ptr<Actor> new_door = world.GetCurrScene()->GetDoorWithId(door_id);

		if (new_door)
		{
			// check all 4 directions of new door to find a space to spawn player
			int map_w = 0;
			int map_h = 0;
			world.GetCurrScene()->GetCoordinateByPosition(*new_door->GetTransform(), map_w, map_h);

			Vector2D top = world.GetCurrScene()->GetPositionByCoordinate(map_w, map_h + 1);
			Vector2D down = world.GetCurrScene()->GetPositionByCoordinate(map_w, map_h - 1);
			Vector2D left = world.GetCurrScene()->GetPositionByCoordinate(map_w - 1, map_h);
			Vector2D right = world.GetCurrScene()->GetPositionByCoordinate(map_w + 1, map_h);

			if (world.GetCurrScene()->IsSpaceFree(top))
			{
				world.GetPlayer()->SetActorPosition(top.X(), top.Y() + TILE_SIZE_HALF, FacingDirection::UP);
				return;
			}
			if (world.GetCurrScene()->IsSpaceFree(down))
			{
				world.GetPlayer()->SetActorPosition(down.X(), down.Y() - TILE_SIZE_HALF, FacingDirection::DOWN);
				return;
			}
			if (world.GetCurrScene()->IsSpaceFree(left))
			{
				world.GetPlayer()->SetActorPosition(left.X() - TILE_SIZE_HALF, left.Y(), FacingDirection::LEFT);
				return;
			}
			if (world.GetCurrScene()->IsSpaceFree(right))
			{
				world.GetPlayer()->SetActorPosition(right.X() + TILE_SIZE_HALF, right.Y(), FacingDirection::RIGHT);
				return;
			}
		}
	}
	else
	{
		world.GameEnd(GameEndType::ESCAPED);
	}

}
