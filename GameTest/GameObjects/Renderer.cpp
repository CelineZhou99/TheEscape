#include "stdafx.h"
#include "Renderer.h"
#include "Actor.h"

void Renderer::CreateSpriteAnimation(float speed, std::vector<int> frames_down, std::vector<int> frames_left, std::vector<int> frames_right, std::vector<int> frames_up)
{
	_sprite->CreateAnimation(FacingDirection::DOWN, speed, frames_down);
	_sprite->CreateAnimation(FacingDirection::LEFT, speed, frames_left);
	_sprite->CreateAnimation(FacingDirection::RIGHT, speed, frames_right);
	_sprite->CreateAnimation(FacingDirection::UP, speed, frames_up);
}

void Renderer::UpdateSpriteAnimation(float delta_time)
{
	_sprite->Update(delta_time);
}

void Renderer::SetAnimationWithMovement(FacingDirection direction, float move_by_x, float move_by_y)
{
	float x, y;
	_sprite->GetPosition(x, y);
	_sprite->SetPosition(x + move_by_x, y + move_by_y);
	_sprite->SetAnimation(direction);
}

void Renderer::SetAnimation(FacingDirection direction)
{
	_sprite->SetAnimation(direction);
}

void Renderer::MoveSpritePosition(float x, float y)
{
	float old_x, old_y;
	_sprite->GetPosition(old_x, old_y);
	float new_x = old_x + x;
	float new_y = old_y + y;
	_sprite->SetPosition(new_x, new_y);
}

void Renderer::SetSprite(const char* file_name, unsigned int columns, unsigned int rows)
{
	_sprite = std::make_shared<CSimpleSprite>(*(App::CreateSprite(file_name, columns, rows)));
}

void Renderer::SetSpritePosition(float x, float y, FacingDirection direction)
{
	_sprite->SetPosition(x, y);
	_sprite->SetAnimation(direction);
}
