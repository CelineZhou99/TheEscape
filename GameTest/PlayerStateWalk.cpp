#include "stdafx.h"
#include "PlayerStateWalk.h"
#include "Player.h"

void PlayerStateWalk::SetSpriteImage()
{
	float x, y;
	_player->GetRenderer()->GetSprite()->GetPosition(x, y);
	_player->GetRenderer()->SetSprite(".\\Images\\WalkAnimation.bmp", 3, 4);
	//_player->GetRenderer()->CreateSpriteAnimation(ANIMATION_SPEED, { 0, 1, 2 }, { 3, 4, 5 }, { 6, 7, 8 }, { 9, 10, 11 });
	_player->GetRenderer()->GetSprite()->SetPosition(x, y);
}
