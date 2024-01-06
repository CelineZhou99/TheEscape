#include "stdafx.h"
#include "PlayerStateIdle.h"
#include "../GameObjects/Player.h"

void PlayerStateIdle::SetSpriteImage()
{
	float x, y = 0;
	_player->GetRenderer()->GetSprite()->GetPosition(x, y);
	_player->GetRenderer()->SetSprite(IMAGE_PLAYER_IDLE, 4, 4);
	_player->GetRenderer()->CreateSpriteAnimation(ANIMATION_SPEED, { 0, 1, 2, 3 }, { 4, 5, 6, 7 }, { 8, 9, 10, 11 }, { 12, 13, 14, 15 });
	_player->GetRenderer()->GetSprite()->SetPosition(x, y);
}
