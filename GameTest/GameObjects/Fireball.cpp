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
		if (enemy.IsDead())
		{
			// TODO : MOVE THIS LOGIC INTO THE ENEMY CLASS AS ON DEATH
			if (scene->GetGoalType() == GoalType::GOAL_SLIME)
			{
				scene->GetGoal()->DecrementContextCount();
				scene->GetGoal()->NotifySubscribers();
			}
			scene->RemoveFromSceneLayers(object, LayerType::CHARACTERS);
		}
	}
	else if (object->GetTag() == TagType::DESTRUCTABLE)
	{
		Pot& pot = static_cast<Pot&>(*object);
		pot.TakeDamage();
		if (pot.IsDead())
		{
			scene->RemoveFromSceneLayers(object, LayerType::FOREGROUND);
		}
	}
	scene->RemoveFromSceneLayers(this, LayerType::SPELLS);
}
