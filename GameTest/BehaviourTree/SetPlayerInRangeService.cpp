#include "stdafx.h"
#include "SetPlayerInRangeService.h"
#include "../Scenes/Scene.h"
#include "../GameObjects/Player.h"
#include "../GameObjects/Slime.h"
#include "Blackboard.h"

BehaviourNodeState SetPlayerInRangeService::AssessCurrState()
{
 	int slime_w = 0;
	int slime_h = 0;
	_scene->GetCoordinateByPosition(*_slime->GetTransform(), slime_w, slime_h);

	int player_w = 0;
	int player_h = 0;
	_scene->GetCoordinateByPosition(*_player->GetTransform(), player_w, player_h);

	int aggro_range = _slime->GetAggroRange();
	int start_x = max(0, slime_w - aggro_range);
	int end_x = min(MAP_WIDTH - 1, slime_w + aggro_range);
	int start_y = max(0, slime_h + aggro_range);
	int end_y = min(MAP_HEIGHT - 1, slime_h - aggro_range);

	// if player is within aggro range, set the player blackboard variable, otherwise remove it
	if (player_w >= start_x && player_w <= end_x && player_h <= start_y && player_h >= end_y)
	{
		_blackboard->SetVariable(BLACKBOARD_PLAYER, new Any<Player*>(_player));
	}
	else
	{
		_blackboard->RemoveVariable(BLACKBOARD_PLAYER);
	}

	return BehaviourNodeState::SUCCESS;
}
