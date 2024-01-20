#include "stdafx.h"
#include "World.h"
#include "GameObjects/Actor.h"
#include "GameObjects/PressurePlate.h"
#include "GameObjects/Key.h"
#include "GameObjects/Slime.h"
#include "GameObjects/ResetButton.h"

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

	text_box.SetSpriteLocation(TEXT_BOX_X, TEXT_BOX_Y);
	text_box.SetDialogue(&game_start_dialogue);
}

void World::Update(float deltaTime)
{
	if (!player) { return; }

	if (!App::IsSoundPlaying(NORMAL_MUSIC))
	{
		App::PlaySound(NORMAL_MUSIC, true);
	}

	if (!text_box.GetIsDialogueFinished()) { return; }

	//------------------------------------------------------------------------
	// Handle player
	//------------------------------------------------------------------------

	if (player->GetIsInvulnerable())
	{
		InvulnerabilityCountdown(deltaTime);
		player->GetRenderer()->GetSprite()->SetColor(0.66, 0.66, 0.66);
	}
	else
	{
		player->GetRenderer()->GetSprite()->SetColor(1, 1, 1);
	}

	BoxCollider collider(*player->GetCollider());
	FacingDirection direction = player->GetLastFacingDirection();
	float player_move_by_x = 0;
	float player_move_by_y = 0;

	// rename this better 
	bool player_will_move = CalculatePlayerNextMovement(collider, direction, player_move_by_x, player_move_by_y);

	if (player_will_move)
	{
		player->SetState(PlayerStateType::WALK);
		if (ShouldPlayerMove(collider, direction))
		{
			player_controller->UpdateControlledActorPosition(player_move_by_x, player_move_by_y, direction);
		}
	}
	else
	{
		player->SetState(PlayerStateType::IDLE);
		player->GetRenderer()->SetAnimation(direction);
	}

	object_list character_layer = current_scene->GetSceneLayers().at(LayerType::CHARACTERS);
	for (std::shared_ptr<GameObject> character : character_layer)
	{
		character->GetRenderer()->UpdateSpriteAnimation(deltaTime);
		if (character->GetTag() == TagType::ENEMY)
		{
			Slime& enemy = static_cast<Slime&>(*character.get());
			enemy.GetBehaviourTree()->Update();
		}
	}

	CheckShootControls();
	UpdateSpells();

	// TODO : could make it a subscribe pattern here 
	if (player->IsDead())
	{
		GameEndDead();
		return;
	}
}

bool World::CalculatePlayerNextMovement(ICollider& collider, FacingDirection& direction, float& player_move_by_x, float& player_move_by_y)
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

bool World::ShouldPlayerMove(ICollider& collider, FacingDirection& direction)
{
	std::vector<std::vector<std::shared_ptr<GameObject>>> scene_layers = current_scene->GetSceneLayers();

	for (std::shared_ptr<GameObject> object : scene_layers[LayerType::CHARACTERS])
	{
		if (object->GetTag() == TagType::ENEMY)
		{
			Actor& actor = static_cast<Actor&>(*object.get());
			if (player->GetCollider()->CheckCollision(collider, *actor.GetCollider()))
			{
				player->TakeDamage();
				return false;
			}
		}
	}
	for (std::shared_ptr<GameObject> object : scene_layers[LayerType::FOREGROUND])
	{
		Actor& actor = static_cast<Actor&>(*object.get());
		if (player->GetCollider()->CheckCollision(collider, *actor.GetCollider()))
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
			else if (actor.GetTag() == TagType::BUTTON)
			{
				ResetButton& button = static_cast<ResetButton&>(actor);
				button.OnInteractWithPlayer(*this);
			}
			return false;
		}
	}
	for (std::shared_ptr<GameObject> object : scene_layers[LayerType::MIDDLEGROUND])
	{
		Actor& actor = static_cast<Actor&>(*object.get());
		if (player->GetCollider()->CheckCollision(collider, *actor.GetCollider()))
		{
			if (actor.GetTag() != TagType::PLATE)
			{
				if (actor.GetTag() == TagType::DOOR)
				{
					Door& door = static_cast<Door&>(actor);
					door.OnInteractWithPlayer(*this);
				}
				return false;
			} 
		}
	}
	
	return true;
}

bool World::ShouldMovableObjectsMove(Actor& actor_to_move, ICollider& collider, FacingDirection& direction)
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

void World::InvulnerabilityCountdown(float deltaTime)
{
	start_timer += deltaTime / 1000;
	if (start_timer >= stop_timer)
	{
		start_timer = 0.f;
		player->SetIsInvulnerable(false);
	}
}

void World::CheckShootControls()
{
	if (!player->GetCanShoot())
	{
		return;
	}

	int map_w = 0;
	int map_h = 0;
	current_scene->GetCoordinateByPosition(*player->GetTransform(), map_w, map_h);

	// spawn fireball in the direction the player selected via the arrow keys 
	if (App::IsKeyPressed('I') && !is_up_pressed)
	{
		is_up_pressed = true;
	}
	if (!App::IsKeyPressed('I') && is_up_pressed)
	{
		is_up_pressed = false;
		// spawn fireball on key release
		Vector2D position = current_scene->GetPositionByCoordinate(map_w, map_h + 1);
		if (current_scene->IsSpaceFree(position))
		{
			current_scene->MakeFireball(position.X(), position.Y(), FacingDirection::UP);
		}
	}

	if (App::IsKeyPressed('K') && !is_down_pressed)
	{
		is_down_pressed = true;
	}
	if (!App::IsKeyPressed('K') && is_down_pressed)
	{
		is_down_pressed = false;
		Vector2D position = current_scene->GetPositionByCoordinate(map_w, map_h - 1);
		if (current_scene->IsSpaceFree(position))
		{
			current_scene->MakeFireball(position.X(), position.Y(), FacingDirection::DOWN);
		}
	}

	if (App::IsKeyPressed('J') && !is_left_pressed)
	{
		is_left_pressed = true;
	}
	if (!App::IsKeyPressed('J') && is_left_pressed)
	{
		is_left_pressed = false;
		Vector2D position = current_scene->GetPositionByCoordinate(map_w - 1, map_h);
		if (current_scene->IsSpaceFree(position))
		{
			current_scene->MakeFireball(position.X(), position.Y(), FacingDirection::LEFT);
		}
	}

	if (App::IsKeyPressed('L') && !is_right_pressed)
	{
		is_right_pressed = true;
	}
	if (!App::IsKeyPressed('L') && is_right_pressed)
	{
		is_right_pressed = false;
		Vector2D position = current_scene->GetPositionByCoordinate(map_w + 1, map_h);
		if (current_scene->IsSpaceFree(position))
		{
			current_scene->MakeFireball(position.X(), position.Y(), FacingDirection::RIGHT);
		}
	}
}

void World::UpdateSpells()
{
	object_list spells = current_scene->GetSceneLayers().at(LayerType::SPELLS);
	for (std::shared_ptr<GameObject> object : spells)
	{
		Fireball& fireball = static_cast<Fireball&>(*object.get());
		switch (fireball.GetFacingDirection())
		{
		case FacingDirection::UP:
			fireball.UpdateActorPosition(0, 5);
			break;
		case FacingDirection::DOWN:
			fireball.UpdateActorPosition(0, -5);
			break;
		case FacingDirection::LEFT:
			fireball.UpdateActorPosition(-5, 0);
			break;
		case FacingDirection::RIGHT:
			fireball.UpdateActorPosition(5, 0);
			break;
		}
		CheckSpellCollision(fireball);
	}
}

void World::CheckSpellCollision(Fireball& fireball)
{
	object_list characters = current_scene->GetSceneLayers().at(LayerType::CHARACTERS);
	for (std::shared_ptr<GameObject> object : characters)
	{
		Actor& actor = static_cast<Actor&>(*object.get());
		if (fireball.GetCollider()->CheckCollision(*fireball.GetCollider(), *actor.GetCollider()))
		{
			fireball.OnCollideWithObject(object.get(), current_scene.get());
			return;
		}
	}

	object_list foreground = current_scene->GetSceneLayers().at(LayerType::FOREGROUND);
	for (std::shared_ptr<GameObject> object : foreground)
	{
		Actor& actor = static_cast<Actor&>(*object.get());
		if (fireball.GetCollider()->CheckCollision(*fireball.GetCollider(), *actor.GetCollider()))
		{
			fireball.OnCollideWithObject(object.get(), current_scene.get());
			return;
		}
	}

	object_list middleground = current_scene->GetSceneLayers().at(LayerType::MIDDLEGROUND);
	for (std::shared_ptr<GameObject> object : middleground)
	{
		Actor& actor = static_cast<Actor&>(*object.get());
		if (fireball.GetCollider()->CheckCollision(*fireball.GetCollider(), *actor.GetCollider()))
		{
			fireball.OnCollideWithObject(object.get(), current_scene.get());
			return;
		}
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

void World::DrawTextBox()
{
	text_box.DrawSprite();
	text_box.DisplayDialogue();
}

void World::GameEndEscaped()
{
	// TODO: MERGE THE GAME END ESCAPE AND GAME END DEAD
	has_game_ended = true;
	end_screen_sprite = std::make_unique<CSimpleSprite>(END_SCREEN);
	end_screen_sprite->SetPosition(512, 384);

	App::StopSound(NORMAL_MUSIC);
	App::PlaySound(END_MUSIC);
}

void World::GameEndDead()
{
	has_game_ended = true;
	end_screen_sprite = std::make_unique<CSimpleSprite>(DEAD_SCREEN);
	end_screen_sprite->SetPosition(512, 384);

	App::StopSound(NORMAL_MUSIC);
	App::PlaySound(DEAD_MUSIC);
}
