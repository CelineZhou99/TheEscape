#include "stdafx.h"
#include "Renderer.h"

void Renderer::CreateSpriteAnimation(float speed, std::vector<int> frames_down, std::vector<int> frames_left, std::vector<int> frames_right, std::vector<int> frames_up)
{
	_sprite->CreateAnimation(FacingDirection::DOWN, speed, frames_down);
	_sprite->CreateAnimation(FacingDirection::LEFT, speed, frames_left);
	_sprite->CreateAnimation(FacingDirection::RIGHT, speed, frames_right);
	_sprite->CreateAnimation(FacingDirection::UP, speed, frames_up);
}

void Renderer::UpdateSprite(float delta_time)
{
	_sprite->Update(delta_time);
}

void Renderer::SetAnimation(FacingDirection direction)
{
	_sprite->SetAnimation(direction);
	float x, y;
	_sprite->GetPosition(x, y);
	switch (direction)
	{
	case FacingDirection::UP:
		y += 1.0f;
		_sprite->SetPosition(x, y);
		break;
	case FacingDirection::DOWN:
		y -= 1.0f;
		_sprite->SetPosition(x, y);
		break;
	case FacingDirection::LEFT:
		x -= 1.0f;
		_sprite->SetPosition(x, y);
		break;
	case FacingDirection::RIGHT:
		x += 1.0f;
		_sprite->SetPosition(x, y);
		break;
	}
}