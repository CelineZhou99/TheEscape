#include "stdafx.h"
#include "World.h"
#include "GameObjects/Actor.h"
#include "GameObjects/PressurePlate.h"
#include "GameObjects/Key.h"
#include "GameObjects/Slime.h"
#include "GameObjects/ResetButton.h"
#include "GameObjects/GummyBear.h"
#include "GameObjects/Fireball.h"
#include "GameObjects/HealthComponent.h"

void World::Init()
{
	spawned_rewards = {};
	_unlocked_doors = {};
	current_goal = std::make_shared<Goal>(*this);
	current_scene = std::make_unique<Scene>(current_goal.get());
	std::shared_ptr<Renderer> renderer(new Renderer(IMAGE_PLAYER_IDLE, 4, 4, PLAYER_START_X, PLAYER_START_Y));
	std::shared_ptr<HealthComponent> health_component = std::make_shared<HealthComponent>(3);
	player = std::make_shared<Player>(current_scene->AllocateId(), renderer, PLAYER_START_X, PLAYER_START_Y, TagType::PLAYER, health_component);
	player->GetRenderer()->CreateSpriteAnimation(ANIMATION_SPEED, { 0, 1, 2, 3 }, { 4, 5, 6, 7 }, { 8, 9, 10, 11 }, { 12, 13, 14, 15 });

	current_scene->AddToSceneLayers(player, LayerType::CHARACTERS);
	current_scene->LoadMap(STARTING_MAP);
	current_goal->SetGoalType(current_scene->GetGoalType());
	current_goal->Subscribe(current_scene.get());

	text_box = std::make_shared<TextBox>(IMAGE_TEXT_BOX);
	text_box->SetSpriteLocation(TEXT_BOX_X, TEXT_BOX_Y);

	Dialogue start_dialogue = {
		"Where am I...?",
		"I can't remember much...",
		"I can hear the faint sound of birds from that door...",
		"That must be the exit."
	};
	if (has_game_reset)
	{
		start_dialogue.push_back("...");
		start_dialogue.push_back("Wait... why do I feel a sense of deja vu...?");
	}
	game_start_dialogue = std::make_shared<Dialogue>(start_dialogue);

	text_box->SetDialogue(game_start_dialogue.get());
}

void World::Update(float deltaTime)
{
	if (!player) { return; }

	if (!App::IsSoundPlaying(NORMAL_MUSIC))
	{
		App::PlaySound(NORMAL_MUSIC, true);
	}

	if (!text_box->GetIsDialogueFinished()) { return; }

	//------------------------------------------------------------------------
	// Handle player
	//------------------------------------------------------------------------
	BoxCollider collider(*player->GetCollider());
	FacingDirection direction = player->GetLastFacingDirection();
	float player_move_by_x = 0;
	float player_move_by_y = 0;

	bool player_requested_move = CalculatePlayerNextMovement(collider, direction, player_move_by_x, player_move_by_y);

	bool player_will_move = false;

	if (player_requested_move)
	{
		player_will_move = ShouldPlayerMove(collider, direction);
	}

	player->Update(deltaTime, player_requested_move, player_will_move, direction, player_move_by_x, player_move_by_y);

	ObjectsList character_list = current_scene->GetSceneLayers().at(LayerType::CHARACTERS);
	for (GameObjectPtr character : character_list)
	{
		character->Update(deltaTime, current_scene.get());
	}

	if (player->GetCanShoot())
	{
		FacingDirection spell_direction = FacingDirection::NONE;
		if (CheckShootControls(spell_direction))
		{
			current_scene->SpawnFireball(*player->GetTransform(), spell_direction);
		}
	}

	UpdateSpells(deltaTime);

	if (player->GetHealthComponent()->IsDead())
	{
		GameEnd(GameEndType::DEAD);
		return;
	}
}

bool World::CalculatePlayerNextMovement(ColliderBase& collider, FacingDirection& direction, float& player_move_by_x, float& player_move_by_y)
{
	bool player_will_move = true;
	if (App::IsKeyPressed('W'))
	{
		direction = FacingDirection::UP;
		player_move_by_y = player->GetSpeed();
	}
	else if (App::IsKeyPressed('S'))
	{
		direction = FacingDirection::DOWN;
		player_move_by_y = -player->GetSpeed();
	}
	else if (App::IsKeyPressed('A'))
	{
		direction = FacingDirection::LEFT;
		player_move_by_x = -player->GetSpeed();
	}
	else if (App::IsKeyPressed('D'))
	{
		direction = FacingDirection::RIGHT;
		player_move_by_x = player->GetSpeed();
	} 
	else
	{
		return false;
	}

	collider.MoveColliderPosition(player_move_by_x, player_move_by_y);

	return player_will_move;
}

bool World::ShouldPlayerMove(ColliderBase& collider, FacingDirection& direction)
{
	SceneLayersList scene_layer = current_scene->GetSceneLayers();

	for (GameObjectPtr object : scene_layer[LayerType::CHARACTERS])
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
	for (GameObjectPtr object : scene_layer[LayerType::FOREGROUND])
	{
		Actor& actor = static_cast<Actor&>(*object.get());
		if (player->GetCollider()->CheckCollision(collider, *actor.GetCollider()))
		{
			if (actor.GetTag() == TagType::BOX)
			{
				UpdateMovableObjects(actor, direction, object.get());
				return false;
			}
			else if (actor.GetTag() == TagType::ITEM)
			{
				Item& item = static_cast<Item&>(actor);
				if (item.GetItemType() == ItemType::KEY || item.GetItemType() == ItemType::KEY_ESCAPE)
				{
					Key& key = static_cast<Key&>(item);
					key.OnInteractWithPlayer(*this);
				}
				else if (item.GetItemType() == ItemType::GUMMY_BEAR)
				{
					GummyBear& bear = static_cast<GummyBear&>(item);
					bear.OnInteractWithPlayer(*this);
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
	for (GameObjectPtr object : scene_layer[LayerType::MIDDLEGROUND])
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

bool World::ShouldMovableObjectsMove(Actor& actor_to_move, ColliderBase& collider, FacingDirection& direction)
{
	bool should_move = true;
	SceneLayersList scene_layer = current_scene->GetSceneLayers();

	for (GameObjectPtr object : scene_layer[LayerType::FOREGROUND])
	{
		Actor& actor = static_cast<Actor&>(*object.get());
		if (actor_to_move.GetCollider()->CheckCollision(collider, *actor.GetCollider()))
		{
			should_move = false;
			break;
		}
	}
	for (GameObjectPtr object : scene_layer[LayerType::MIDDLEGROUND])
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
				PressurePlate& pressure_plate = static_cast<PressurePlate&>(actor);
				pressure_plate.SetState(PressurePlateStateType::ON, current_goal.get());
				break;
			}
		}
	}
	return should_move;
}

void World::UpdateMovableObjects(Actor& actor, FacingDirection direction, GameObject* object)
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
		SceneLayersList scene_layer = current_scene->GetSceneLayers();
		// check if it is already colliding with any pressure plates
		// if it is, change the state of that pressure plate
		for (GameObjectPtr objects : scene_layer[LayerType::MIDDLEGROUND])
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
		App::PlaySound(BOX_MOVE_SOUND);
		Vector2D old_position = *actor.GetTransform();
		actor.UpdateActorPosition(move_by_x, move_by_y);
		current_scene->MoveObjectPositionInMap(old_position, *actor.GetTransform(), object);
	}
}

bool World::OnKeyUp(char key, bool& key_variable)
{
	if (App::IsKeyPressed(key) && !key_variable)
	{
		key_variable = true;
	}
	if (!App::IsKeyPressed(key) && key_variable)
	{
		key_variable = false;
		return true;
	}
	return false;
}

bool World::CheckShootControls(FacingDirection& direction)
{
	// I, K, J, L corresponds to UP, DOWN, LEFT, RIGHT for spell directions
	// if two keys are pressed and released at the same time, only one direction will work
	if (OnKeyUp('I', is_up_pressed))
	{
		direction = FacingDirection::UP;
		is_down_pressed = false;
		is_left_pressed = false;
		is_right_pressed = false;
		return true;
	}

	if (OnKeyUp('K', is_down_pressed))
	{
		direction = FacingDirection::DOWN;
		is_up_pressed = false;
		is_left_pressed = false;
		is_right_pressed = false;
		return true;
	}

	if (OnKeyUp('J', is_left_pressed))
	{
		direction = FacingDirection::LEFT;
		is_up_pressed = false;
		is_down_pressed = false;
		is_right_pressed = false;
		return true;
	}

	if (OnKeyUp('L', is_right_pressed))
	{
		direction = FacingDirection::RIGHT;
		is_up_pressed = false;
		is_down_pressed = false;
		is_left_pressed = false;
		return true;
	}
	return false;
}

void World::UpdateSpells(float deltaTime)
{
	ObjectsList spells = current_scene->GetSceneLayers().at(LayerType::SPELLS);
	for (GameObjectPtr object : spells)
	{
		object->Update(deltaTime, current_scene.get());
	}
}

void World::DrawAllSprites()
{
	for (size_t i = 0; i < LayerType::COUNT; ++i)
	{
		ObjectsList objects = current_scene->GetSceneLayers().at(i);
		for (GameObjectPtr actor : objects)
		{
			actor->GetRenderer()->DrawSprite();
		}
	}
}

void World::DrawUI()
{
	float x = UI_START_X;
	float y = UI_START_Y;
	for (size_t i = 0; i < player->GetHealthComponent()->GetHealth(); ++i)
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
	text_box->DrawSprite();
	text_box->DisplayDialogue();
}

void World::GameEnd(GameEndType game_end_type)
{
	has_game_ended = true;
	const char* file_name = game_end_type == GameEndType::ESCAPED ? END_SCREEN : DEAD_SCREEN;

	end_screen_sprite = std::make_unique<CSimpleSprite>(file_name);
	end_screen_sprite->SetPosition(512, 384);

	App::StopSound(NORMAL_MUSIC);

	const char* music_file = game_end_type == GameEndType::ESCAPED ? END_MUSIC : DEAD_MUSIC;
	App::PlaySound(music_file);
}
