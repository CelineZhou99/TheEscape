#include "stdafx.h"
#include "PlayerController.h"

bool PlayerController::IsMoving()
{
    if (velocity > 0)
    {
        return true;
    }
    return false;
}

void PlayerController::UpdatePlayerPosition(float move_by_x, float move_by_y, FacingDirection direction)
{
    controlled_actor->GetTransform().MoveVectorPosition(move_by_x, move_by_y);
    controlled_actor->GetRenderer()->SetAnimation(direction);
    controlled_actor->GetCollider()->MoveColliderPosition(move_by_x, move_by_y);
}
