#pragma once

#include "App/app.h"
//------------------------------------------------------------------------
enum FacingDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};
//------------------------------------------------------------------------
class Renderer
{
public:
	Renderer(const char* file_name, unsigned int columns, unsigned int rows, float x, float y)
	{
		_sprite = std::make_shared<CSimpleSprite>(*(App::CreateSprite(file_name, columns, rows)));
		_sprite->SetPosition(x, y);
	}
	void CreateSpriteAnimation(float speed, std::vector<int> frames_down, std::vector<int> frames_left, std::vector<int> frames_right, std::vector<int> frames_up);
	void UpdateSpriteAnimation(float delta_time);
	void SetAnimation(FacingDirection direction);

	// move the sprite position by the provided x, y amount
	void MoveSpritePosition(float x, float y);

	void DrawSprite() { _sprite->Draw(); }

	void SetSprite(const char* file_name, unsigned int columns, unsigned int rows);
	std::shared_ptr<CSimpleSprite> GetSprite() { return _sprite; }

private:
	std::shared_ptr<CSimpleSprite> _sprite;
};

