#include "stdafx.h"
#include "PlayerController.h"

void PlayerController::UpdateControlledActorPosition(float move_by_x, float move_by_y, FacingDirection direction)
{
    _controlled_actor->GetTransform()->MoveVectorPosition(move_by_x, move_by_y);
    _controlled_actor->GetRenderer()->SetAnimationWithMovement(direction, move_by_x, move_by_y);
    _controlled_actor->GetCollider()->MoveColliderPosition(move_by_x, move_by_y);
    GetControlledActor()->SetLastFacingDirection(direction);
}

void PlayerController::SetControlledActorPosition(float x, float y, FacingDirection direction)
{
    _controlled_actor->GetTransform()->SetVectorPosition(x, y);
    _controlled_actor->GetRenderer()->SetSpritePosition(x, y, direction);
    float top_left_x = x - _controlled_actor->GetRenderer()->GetSprite()->GetWidth() / 2;
    float top_left_y = y + _controlled_actor->GetRenderer()->GetSprite()->GetHeight() / 2;
    _controlled_actor->GetCollider()->SetColliderPosition(top_left_x, top_left_y);
}

Player* PlayerController::GetControlledActor()
{
    Player* player = static_cast<Player*>(_controlled_actor);
    return player;
}
