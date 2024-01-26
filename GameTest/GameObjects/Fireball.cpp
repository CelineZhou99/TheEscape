#include "stdafx.h"
#include "Fireball.h"
#include "Slime.h"
#include "../Scenes/Scene.h"
#include "Pot.h"

void Fireball::OnCollideWithObject(GameObject* object, Scene* scene)
{
	if (object->GetTag() == TagType::ENEMY)
	{
		Slime& enemy = static_cast<Slime&>(*object);
		enemy.TakeDamage();
		App::PlaySound(IMPACT_ENEMY_SOUND);
		if (enemy.GetHealthComponent()->IsDead())
		{
			enemy.OnDeath(scene, LayerType::CHARACTERS);
		}
	}
	else if (object->GetTag() == TagType::DESTRUCTABLE)
	{
		Pot& pot = static_cast<Pot&>(*object);
		pot.TakeDamage();
		App::PlaySound(IMPACT_DESTRUCTABLE_SOUND);
		if (pot.GetHealthComponent()->IsDead())
		{
			pot.OnDeath(scene, LayerType::FOREGROUND);
		}
	}
	else
	{
		App::PlaySound(IMPACT_OBJECT_SOUND);
	}
	// On collide with any object the fireball will disappear
	OnDeath(scene, LayerType::SPELLS);
}

void Fireball::Update(float deltaTime, Scene* scene)
{
	Actor::Update(deltaTime, scene);

	switch (_direction)
	{
	case FacingDirection::UP:
		UpdateActorPosition(0, GetSpeed());
		break;
	case FacingDirection::DOWN:
		UpdateActorPosition(0, -GetSpeed());
		break;
	case FacingDirection::LEFT:
		UpdateActorPosition(-GetSpeed(), 0);
		break;
	case FacingDirection::RIGHT:
		UpdateActorPosition(GetSpeed(), 0);
		break;
	}
	CheckCollision(scene);
}

void Fireball::CheckCollision(Scene* scene)
{
	ObjectsList characters = scene->GetSceneLayers().at(LayerType::CHARACTERS);
	for (GameObjectPtr object : characters)
	{
		// spells should not hit the player themselves
		if (object->GetTag() == TagType::PLAYER)
		{
			continue;
		}
		Actor& actor = static_cast<Actor&>(*object.get());
		if (_collider->CheckCollision(*_collider, *actor.GetCollider()))
		{
			OnCollideWithObject(object.get(), scene);
			return;
		}
	}

	ObjectsList foreground = scene->GetSceneLayers().at(LayerType::FOREGROUND);
	for (GameObjectPtr object : foreground)
	{
		Actor& actor = static_cast<Actor&>(*object.get());
		if (_collider->CheckCollision(*_collider, *actor.GetCollider()))
		{
			OnCollideWithObject(object.get(), scene);
			return;
		}
	}

	ObjectsList middleground = scene->GetSceneLayers().at(LayerType::MIDDLEGROUND);
	for (GameObjectPtr object : middleground)
	{
		Actor& actor = static_cast<Actor&>(*object.get());
		if (_collider->CheckCollision(*_collider, *actor.GetCollider()))
		{
			OnCollideWithObject(object.get(), scene);
			return;
		}
	}
}
