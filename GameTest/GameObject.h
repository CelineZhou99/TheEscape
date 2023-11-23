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

class GameObject
{
public:
	GameObject(Renderer* renderer, float pos_x, float pos_y, TagType tag)
		: _transform(pos_x, pos_y), _renderer(renderer), _tag(tag) {}

	~GameObject() 
	{
		delete _renderer;
	}
	bool IsMoving();
	Vector2D GetTransform() { return _transform; }
	Renderer* GetRenderer() { return _renderer; }
	TagType GetTag() { return _tag; }

protected:
	Vector2D _transform;
	Renderer* _renderer;
	TagType _tag;
};

