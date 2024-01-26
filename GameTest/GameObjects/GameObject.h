#pragma once
//------------------------------------------------------------------------
#include "Vector2D.h"
#include "Renderer.h"
//------------------------------------------------------------------------
enum TagType : uint8_t
{
	STATIC_OBJECT,
	PLAYER,
	ENEMY,
	BOX,
	PLATE,
	DOOR,
	ITEM,
	BUTTON,
	SPELL,
	DESTRUCTABLE,
};

class Scene;

class GameObject
{
public:
	GameObject(unsigned short id, std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag)
		: _transform(std::make_shared<Vector2D>(pos_x, pos_y)), _renderer(renderer), _id(id), _tag(tag) {}

	std::shared_ptr<Vector2D> GetTransform() const { return _transform; }
	std::shared_ptr<Renderer> GetRenderer() const { return _renderer; }
	TagType GetTag() const { return _tag; }

	unsigned short GetId() const { return _id; }

	bool operator == (const GameObject* object) 
	{
		if (object->_id == _id)
		{
			return true;
		}
		return false;
	}

	void Update(float deltaTime, Scene* scene);

protected:
	std::shared_ptr<Vector2D> _transform;
	std::shared_ptr<Renderer> _renderer;
	unsigned short _id;
	TagType _tag;
};

