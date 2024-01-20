#include "stdafx.h"
#include "ResetButton.h"
#include "../World.h"
#include "PressurePlate.h"

void ResetButton::OnInteractWithPlayer(World& world)
{
	if (_original_box_locations.empty() || _is_disabled)
	{
		return;
	}

	// Reset button will reset the position of boxes, the pressure plate states, and the goal progress

	object_list foreground = world.current_scene->GetSceneLayers().at(LayerType::FOREGROUND);
	int index = 0;
	for (std::shared_ptr<GameObject> object : foreground)
	{
		if (object->GetTag() == TagType::MOVABLE_OBJECT)
		{
			Actor& actor = static_cast<Actor&>(*object.get());
			actor.SetActorPosition(_original_box_locations[index].X(), _original_box_locations[index].Y());
			++index;
			// TODO : ASK WHY INDEX++ DOESNT WORK HERE
			if (index >= _original_box_locations.size())
			{
				break;
			}
		}
	}

	object_list middleground = world.current_scene->GetSceneLayers().at(LayerType::MIDDLEGROUND);
	for (std::shared_ptr<GameObject> object : middleground)
	{
		if (object->GetTag() == TagType::PLATE)
		{
			PressurePlate& plate = static_cast<PressurePlate&>(*object.get());
			plate.SetState(PressurePlateStateType::OFF, nullptr, true);
		}
	}

	world.current_goal->SetContextCount(_original_goal_context_count);
}

void ResetButton::AddToOriginalBoxLocation(Vector2D& location)
{
	_original_box_locations.push_back(location);
}
