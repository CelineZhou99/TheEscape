#include "stdafx.h"
#include "World.h"
#include "GameObjects/Actor.h"
#include "States/PlayerStateIdle.h"
#include "States/PlayerStateWalk.h"
#include "GameObjects/PressurePlate.h"
#include "GameObjects/Key.h"

void World::Init()
{
	std::shared_ptr<Renderer> renderer(new Renderer(IMAGE_PLAYER_IDLE, 4, 4, PLAYER_START_X, PLAYER_START_Y));
	player = std::make_shared<Player>(renderer, PLAYER_START_X, PLAYER_START_Y, TagType::PLAYER);
	player->GetRenderer()->CreateSpriteAnimation(ANIMATION_SPEED, { 0, 1, 2, 3 }, { 4, 5, 6, 7 }, { 8, 9, 10, 11 }, { 12, 13, 14, 15 });

	player_controller = std::make_shared<PlayerController>(player.get());

	current_goal = std::make_shared<Goal>();
	current_scene = std::make_unique<Scene>(current_goal.get());
	current_scene->LoadMap(STARTING_MAP);
	current_goal->SetGoalType(current_scene->GetGoalType());
	current_goal->Subscribe(current_scene.get());

	current_scene->AddToSceneLayers(player, LayerType::CHARACTERS);
	
}

void World::Update(float deltaTime)
{
	if (!player) { return; }

	if (!App::IsSoundPlaying(NORMAL_MUSIC))
	{
		PlayMusic();
	}
	//------------------------------------------------------------------------
	// Handle player movement
	//------------------------------------------------------------------------
	BoxCollider collider(*player->GetCollider());
	// set direction to down by default for now
	FacingDirection direction = player->GetLastFacingDirection();
	float player_move_by_x = 0;
	float player_move_by_y = 0;

	bool player_will_move = CalculatePlayerNextMovement(collider, direction, player_move_by_x, player_move_by_y);

	if (player_will_move)
	{
		player->SetState(PlayerStateType::WALK);
		if (ShouldActorMove(*player, collider, direction))
		{
			player_controller->UpdatePlayerPosition(player_move_by_x, player_move_by_y, direction);
		}
	} 
	else
	{
		player->SetState(PlayerStateType::IDLE);
		player->GetRenderer()->SetAnimation(direction);
	}

	player->GetRenderer()->UpdateSpriteAnimation(deltaTime);

}

bool World::CalculatePlayerNextMovement(Collider& collider, FacingDirection& direction, float& player_move_by_x, float& player_move_by_y)
{
	bool player_will_move = true;
	if (App::IsKeyPressed('W'))
	{
		direction = FacingDirection::UP;
		player_move_by_y = PLAYER_MOVE_BY;
	}
	else if (App::IsKeyPressed('S'))
	{
		direction = FacingDirection::DOWN;
		player_move_by_y = -PLAYER_MOVE_BY;
	}
	else if (App::IsKeyPressed('A'))
	{
		direction = FacingDirection::LEFT;
		player_move_by_x = -PLAYER_MOVE_BY;
	}
	else if (App::IsKeyPressed('D'))
	{
		direction = FacingDirection::RIGHT;
		player_move_by_x = PLAYER_MOVE_BY;
	} 
	else
	{
		return false;
	}

	collider.MoveColliderPosition(player_move_by_x, player_move_by_y);

	return player_will_move;
}

bool World::ShouldActorMove(Actor& actor_to_move, Collider& collider, FacingDirection& direction)
{
	bool should_move = true;
	std::vector<std::vector<std::shared_ptr<GameObject>>> scene_layers = current_scene->GetSceneLayers();

	for (std::shared_ptr<GameObject> object : scene_layers[LayerType::FOREGROUND])
	{
		Actor& actor = static_cast<Actor&>(*object.get());
		if (actor_to_move.GetCollider()->CheckCollision(collider, *actor.GetCollider()))
		{
			if (actor.GetTag() == TagType::MOVABLE_OBJECT)
			{
				// TODO: FIX BUG WHERE IF PLAYER TOUCHES 2 MOVABLE OBJECTS THEY WILL MOVE BOTH
				UpdateMovableObjects(actor, direction);
				return false;
			}
			else if (actor.GetTag() == TagType::ITEM)
			{
				// TODO: ASK HOW TO USE DYNAMIC CAST
				Item& item = static_cast<Item&>(actor);
				if (item.GetItemType() == ItemType::KEY || item.GetItemType() == ItemType::KEY_ESCAPE)
				{
					Key& key = static_cast<Key&>(item);
					key.OnInteractWithPlayer(*this);
				}
			}
			should_move = false;
			break;
		}
	}

	for (std::shared_ptr<GameObject> object : scene_layers[LayerType::MIDDLEGROUND])
	{
		Actor& actor = static_cast<Actor&>(*object.get());
		if (actor_to_move.GetCollider()->CheckCollision(collider, *actor.GetCollider()))
		{
			if (actor.GetTag() != TagType::PLATE)
			{
				if (actor.GetTag() == TagType::DOOR)
				{
					Door& door = static_cast<Door&>(actor);
					door.OnInteractWithPlayer(*this);
				}
				should_move = false;
				break;
			} 
		}
	}
	
	return should_move;
}

bool World::ShouldMovableObjectsMove(Actor& actor_to_move, Collider& collider, FacingDirection& direction)
{
	bool should_move = true;
	std::vector<std::vector<std::shared_ptr<GameObject>>> scene_layers = current_scene->GetSceneLayers();

	for (std::shared_ptr<GameObject> object : scene_layers[LayerType::FOREGROUND])
	{
		Actor& actor = static_cast<Actor&>(*object.get());
		if (actor_to_move.GetCollider()->CheckCollision(collider, *actor.GetCollider()))
		{
			should_move = false;
			break;
		}
	}
	for (std::shared_ptr<GameObject> object : scene_layers[LayerType::MIDDLEGROUND])
	{
		Actor& actor = static_cast<Actor&>(*object.get());
		if (actor_to_move.GetCollider()->CheckCollision(collider, *actor.GetCollider()))
		{
			if (actor.GetTag() != TagType::PLATE)
			{
				should_move = false;
				break;
			}
			else if (actor.GetTag() == TagType::PLATE)
			{
				// use static cast to get the derived class
				PressurePlate& pressure_plate = static_cast<PressurePlate&>(actor);
				pressure_plate.SetState(PressurePlateStateType::ON, current_goal.get());
				break;
			}
		}
	}
	return should_move;
}

void World::UpdateMovableObjects(Actor& actor, FacingDirection direction)
{
	float move_by_x = 0;
	float move_by_y = 0;

	BoxCollider collider(*actor.GetCollider());

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
	collider.MoveColliderPosition(move_by_x, move_by_y);
	bool should_actor_move = ShouldMovableObjectsMove(actor, collider, direction);

	if (should_actor_move)
	{
		std::vector<std::vector<std::shared_ptr<GameObject>>> scene_layers = current_scene->GetSceneLayers();
		// check if it is already colliding with any pressure plates
		// if it is, change the state of that pressure plate
		for (std::shared_ptr<GameObject> objects : scene_layers[LayerType::MIDDLEGROUND])
		{
			Actor& object = static_cast<Actor&>(*objects.get());
			if (object.GetTag() == TagType::PLATE)
			{
 				if (actor.GetCollider()->CheckCollision(*actor.GetCollider(), *object.GetCollider()))
				{
					if (object.GetTransform()->X() == actor.GetTransform()->X() && object.GetTransform()->Y() == actor.GetTransform()->Y())
					{
						PressurePlate& pressure_plate = static_cast<PressurePlate&>(object);
						pressure_plate.SetState(PressurePlateStateType::OFF, current_goal.get());
						break;
					}

				}
			}
		}
		actor.UpdateActorPosition(move_by_x, move_by_y);
	}
}

void World::DrawAllSprites()
{
	for (size_t i = 0; i < LayerType::COUNT; ++i)
	{
		std::vector<std::shared_ptr<GameObject>> objects = current_scene->GetSceneLayers().at(i);
		for (std::shared_ptr<GameObject> actor : objects)
		{
			actor->GetRenderer()->DrawSprite();
		}
	}
}

void World::DrawUI()
{
	float x = UI_START_X;
	float y = UI_START_Y;
	for (size_t i = 0; i < player->GetHealth(); ++i)
	{
		player->GetHealthIcon()->SetSpriteLocation(x, y);
		player->GetHealthIcon()->DrawSprite();
		x += UI_SPACING_X;
	}
	x = UI_START_X;
	y -= UI_SPACING_Y;
	for (std::shared_ptr<Item> item : player->GetInventory()->GetItemList())
	{
		for (size_t i = 0; i < item->GetQuantity(); ++i)
		{
			item->GetUIIcon()->SetSpriteLocation(x, y);
			item->GetUIIcon()->DrawSprite();
			x += UI_SPACING_X;
		}
	}
}

void World::PlayMusic()
{
	App::PlaySound(NORMAL_MUSIC);
}

void World::GameEnd()
{
	HasGameEnded = true;
	end_screen_sprite = std::make_unique<CSimpleSprite>(END_SCREEN);
	end_screen_sprite->SetPosition(512, 384);

	if (App::IsSoundPlaying(NORMAL_MUSIC))
	{
		App::StopSound(NORMAL_MUSIC);
		App::PlaySound(END_MUSIC);
	}
}
