#pragma once
//------------------------------------------------------------------------
#include "Vector2D.h"
#include "Renderer.h"
//------------------------------------------------------------------------
enum TagType : uint8_t
{
	PLAYER,
	ENEMY,
	STATIC_OBJECT,
	MOVABLE_OBJECT,
	PLATE,
	DOOR,
	ITEM,
};

class GameObject
{
public:
	GameObject(std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag)
		: _transform(std::make_shared<Vector2D>(pos_x, pos_y)), _renderer(renderer), _tag(tag) {}

	std::shared_ptr<Vector2D> GetTransform() { return _transform; }
	std::shared_ptr<Renderer> GetRenderer() { return _renderer; }
	TagType GetTag() { return _tag; }

	// TODO : CHANGE THIS TO BE COMPARING ID INSTEAD
	bool operator == (const GameObject* object) {
		if (_renderer->GetFileName() == object->_renderer->GetFileName() &&
			_transform->X() == object->_transform->X() &&
			_transform->Y() == object->_transform->Y())
		{
			return true;
		}
		return false;
	}

protected:
	std::shared_ptr<Vector2D> _transform;
	std::shared_ptr<Renderer> _renderer;
	TagType _tag;
};

