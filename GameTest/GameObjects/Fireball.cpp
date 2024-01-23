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
		if (enemy.IsDead())
		{
			enemy.OnDeath(scene);
		}
	}
	else if (object->GetTag() == TagType::DESTRUCTABLE)
	{
		Pot& pot = static_cast<Pot&>(*object);
		pot.TakeDamage();
		App::PlaySound(IMPACT_DESTRUCTABLE_SOUND);
		if (pot.IsDead())
		{
			pot.OnDeath(scene);
		}
	}
	else
	{
		App::PlaySound(IMPACT_OBJECT_SOUND);
	}
	scene->RemoveFromSceneLayers(this, LayerType::SPELLS);
}
