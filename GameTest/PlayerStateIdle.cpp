#include "stdafx.h"
#include "PlayerStateIdle.h"
#include "Player.h"

void PlayerStateIdle::SetSpriteImage()
{
	float x, y;
	_player->GetRenderer()->GetSprite()->GetPosition(x, y);
	_player->GetRenderer()->SetSprite(".\\Images\\IdleAnimation.bmp", 3, 4);
	//_player->GetRenderer()->CreateSpriteAnimation(ANIMATION_SPEED, { 0, 1, 2 }, { 3, 4, 5 }, { 6, 7, 8 }, { 9, 10, 11 });
	_player->GetRenderer()->GetSprite()->SetPosition(x, y);
}
