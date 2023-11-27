#include "stdafx.h"
#include "World.h"
#include "Actor.h"
#include "Scene.h"

void World::Init()
{
	player = new Actor(new Renderer(".\\Images\\Player.bmp", 1, 1, 400.0f, 400.0f), 400.0f, 400.0f, TagType::PLAYER);
	float speed = 1.0f / 8.0f;
	player->GetRenderer()->CreateSpriteAnimation(speed, { 0,1,2,3 }, { 4,5,6,7 }, { 8,9,10,11 }, { 12,13,14,15 });

	player_controller = new PlayerController(player);

	Scene scene;
	scene.LoadMap(".\\SceneData\\TestMap2.txt", &actors, &game_objects);
}

void World::CalculateNextPlayerMovement(Collider& collider, FacingDirection& direction, float& player_move_by_x, float& player_move_by_y)
{
	if (App::IsKeyPressed('W'))
	{
		collider.MoveColliderPosition(0, 1);
		direction = FacingDirection::UP;
		player_move_by_y = PLAYER_MOVE_BY;
	}
	else if (App::IsKeyPressed('S'))
	{
		collider.MoveColliderPosition(0, -1);
		direction = FacingDirection::DOWN;
		player_move_by_y = -PLAYER_MOVE_BY;
	}
	else if (App::IsKeyPressed('A'))
	{
		collider.MoveColliderPosition(-1, 0);
		direction = FacingDirection::LEFT;
		player_move_by_x = -PLAYER_MOVE_BY;
	}
	else if (App::IsKeyPressed('D'))
	{
		collider.MoveColliderPosition(1, 0);
		direction = FacingDirection::RIGHT;
		player_move_by_x = PLAYER_MOVE_BY;
	}
}

bool World::ShouldPlayerMove(Collider& collider, FacingDirection& direction)
{
	bool should_move = true;

	for (Actor* actor : actors)
	{
		if (player->GetCollider()->CheckCollision(&collider, actor->GetCollider()))
		{
			UpdateMovableObjects(actor, direction);
			should_move = false;
		}
	}
	return should_move;
}

void World::UpdateMovableObjects(Actor* actor, FacingDirection direction)
{
	if (actor->GetTag() == TagType::MOVABLE_OBJECT)
	{
		float move_by_x = 0;
		float move_by_y = 0;
		switch (direction)
		{
		case FacingDirection::UP:
			move_by_y = MOVABLE_OBJECT_MOVE_BY;
			break;
		case FacingDirection::DOWN:
			move_by_y = -MOVABLE_OBJECT_MOVE_BY;
			break;
		case FacingDirection::LEFT:
			move_by_x = -MOVABLE_OBJECT_MOVE_BY;
			break;
		case FacingDirection::RIGHT:
			move_by_x = MOVABLE_OBJECT_MOVE_BY;
			break;
		}
		// make that actor move in the opposite direction of the player
		actor->UpdateActorPosition(move_by_x, move_by_y);
		App::PlaySound(".\\Sounds\\Test.wav");
	}
}
