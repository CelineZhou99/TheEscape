#include "stdafx.h"
#include "PlayerController.h"

void PlayerController::UpdatePlayerPosition(float move_by_x, float move_by_y, FacingDirection direction)
{
    _controlled_actor->GetTransform()->MoveVectorPosition(move_by_x, move_by_y);
    _controlled_actor->GetRenderer()->SetAnimationWithMovement(direction);
    _controlled_actor->GetCollider()->MoveColliderPosition(move_by_x, move_by_y);
}
