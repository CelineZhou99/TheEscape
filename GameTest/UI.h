#pragma once

#include "../App/app.h"

class UI
{
public:
	UI(const char* file_name, unsigned int columns = 1, unsigned int rows = 1) :
		_sprite(std::make_shared<CSimpleSprite>(*(App::CreateSprite(file_name, columns, rows)))) {}

	void SetSpriteLocation(float x, float y) { _sprite->SetPosition(x, y); }
	void DrawSprite() { _sprite->Draw(); }
	void SetScale(float scale) { _sprite->SetScale(scale); }

private:
	std::shared_ptr<CSimpleSprite> _sprite;
};

