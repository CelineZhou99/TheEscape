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
		_sprite = App::CreateSprite(file_name, columns, rows);
		_sprite->SetPosition(x, y);
	}
	void CreateSpriteAnimation(float speed, std::vector<int> frames_down, std::vector<int> frames_left, std::vector<int> frames_right, std::vector<int> frames_up);
	void UpdateSprite(float delta_time);
	void SetAnimation(FacingDirection direction);
	void DrawSprite() { _sprite->Draw(); }

	CSimpleSprite* GetSprite() { return _sprite; }

private:
	CSimpleSprite* _sprite;
};

