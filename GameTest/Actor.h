#pragma once
//------------------------------------------------------------------------
#include "Vector2D.h"
#include "App/app.h"
#include "Renderer.h"
//------------------------------------------------------------------------
class Actor
{
public:
	Actor(const char* file_name, unsigned int columns, unsigned int rows, float pos_x, float pos_y)
	{
		_transform = new Vector2D(pos_x, pos_y);
		_renderer = new Renderer(file_name, columns, rows, pos_x, pos_y);
	}

	bool IsMoving();
	Vector2D* GetTransform() { return _transform; }
	Renderer* GetRenderer() { return _renderer; }

private:
	Vector2D* _transform;
	Renderer* _renderer;
};

