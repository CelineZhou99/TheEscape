#pragma once
//------------------------------------------------------------------------
#include "Vector2D.h"
#include "../App/app.h"
#include "Renderer.h"
//------------------------------------------------------------------------
enum TagType
{
	PLAYER,
	ENEMY,
	STATIC_OBJECT,
	MOVABLE_OBJECT,
	PLATE,
	DOOR
};

class GameObject
{
public:
	GameObject(std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag)
		: _transform(pos_x, pos_y), _renderer(renderer), _tag(tag) {}

	Vector2D GetTransform() { return _transform; }
	std::shared_ptr<Renderer> GetRenderer() { return _renderer; }
	TagType GetTag() { return _tag; }

protected:
	Vector2D _transform;
	std::shared_ptr<Renderer> _renderer;
	TagType _tag;
};

