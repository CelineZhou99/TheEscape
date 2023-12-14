#pragma once
//------------------------------------------------------------------------
#include "Vector2D.h"
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
		: _renderer(renderer), _tag(tag) 
	{
		_transform = std::make_shared<Vector2D>(pos_x, pos_y);
	}

	std::shared_ptr<Vector2D> GetTransform() { return _transform; }
	std::shared_ptr<Renderer> GetRenderer() { return _renderer; }
	TagType GetTag() { return _tag; }

protected:
	std::shared_ptr<Vector2D> _transform;
	std::shared_ptr<Renderer> _renderer;
	TagType _tag;
};

