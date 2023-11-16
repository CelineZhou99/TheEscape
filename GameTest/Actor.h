#pragma once
//------------------------------------------------------------------------
#include "Vector2D.h"
#include "App/app.h"
#include "Renderer.h"
//------------------------------------------------------------------------
enum TagType
{
	PLAYER,
	ENEMY,
	STATIC_OBJECT,
	MOVABLE_OBJECT
};

class Actor
{
public:
	Actor(const char* file_name, unsigned int columns, unsigned int rows, float pos_x, float pos_y, TagType tag) 
		: _transform(Vector2D(pos_x, pos_y)), _renderer(Renderer(file_name, columns, rows, pos_x, pos_y)), _tag(tag) {}

	bool IsMoving();
	Vector2D GetTransform() { return _transform; }
	Renderer GetRenderer() { return _renderer; }
	TagType GetTag() { return _tag; }

protected:
	Vector2D _transform;
	Renderer _renderer;
	TagType _tag;
};

