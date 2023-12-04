#include "stdafx.h"
#include "World.h"
#include "Actor.h"
#include "Scene.h"
#include "PlayerStateIdle.h"
#include "PlayerStateWalk.h"

void World::Init()
{
	std::shared_ptr<Renderer> renderer(new Renderer(".\\Images\\IdleAnimation.bmp", 3, 4, 400.0f, 400.0f));
	player = std::make_shared<Player>(renderer, 400.0f, 400.0f, TagType::PLAYER);
	
	player->GetRenderer()->CreateSpriteAnimation(ANIMATION_SPEED, { 0, 1, 2 }, { 3, 4, 5 }, { 6, 7, 8 }, { 9, 10, 11 });

	player_controller = std::make_shared<PlayerController>(player.get());

	Scene scene;
	scene.LoadMap(".\\SceneData\\TestMap.txt", background_objects, middleground_objects, foreground_objects);
}

void World::Update(float deltaTime)
{
	if (!player) { return; }
	player->GetRenderer()->UpdateSpriteAnimation(deltaTime);
	//------------------------------------------------------------------------
	// Handle player movement
	//------------------------------------------------------------------------
	std::shared_ptr<BoxCollider> collider(new BoxCollider(*player->GetCollider()));
	FacingDirection direction = FacingDirection::NONE;
	float player_move_by_x = 0;
	float player_move_by_y = 0;

	CalculateNextPlayerMovement(*collider, direction, player_move_by_x, player_move_by_y);

	if (ShouldPlayerMove(*collider, direction))
	{
		//player->SetState(std::make_shared<PlayerStateWalk>(player.get()));
		player_controller->UpdatePlayerPosition(player_move_by_x, player_move_by_y, direction);
	}
	else 
	{
		//player->SetState(std::make_shared<PlayerStateIdle>(player.get()));
	}
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

	for (std::shared_ptr<Actor> actor : middleground_objects)
	{
		if (player->GetCollider()->CheckCollision(collider, *actor->GetCollider()))
		{
			if (actor->GetTag() == TagType::PLATE)
			{
				// check state of pressure plate 
			} 
			else
			{
				should_move = false;
			}
		}
	}
	for (std::shared_ptr<Actor> actor : foreground_objects)
	{
		if (player->GetCollider()->CheckCollision(collider, *actor->GetCollider()))
		{
			UpdateMovableObjects(*actor, direction);
			should_move = false;
		}
	}
	return should_move;
}

void World::UpdateMovableObjects(Actor& actor, FacingDirection direction)
{
	if (actor.GetTag() == TagType::MOVABLE_OBJECT)
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
		actor.UpdateActorPosition(move_by_x, move_by_y);
	}
}

void World::DrawAllSprites()
{
	for (std::shared_ptr<GameObject> actor : background_objects)
	{
		actor->GetRenderer()->DrawSprite();
	}
	for (std::shared_ptr<Actor> actor : middleground_objects)
	{
		actor->GetRenderer()->DrawSprite();
	}
	for (std::shared_ptr<Actor> actor : foreground_objects)
	{
		actor->GetRenderer()->DrawSprite();
	}

	player->GetRenderer()->DrawSprite();
}
