#pragma once
#include "Vector2D.h"

class Collider
{
	// abstract class as base for all types of colliders 
public:
	Collider(Vector2D* position, float width, float height)
	{
		_position = position;
		_collider_width = width;
		_collider_height = height;
	}
	// pure virtual function
	virtual bool CheckCollision(Collider* obj_1_collider, Collider* obj_2_collider) = 0;
	void UpdatePosition(float x, float y) { _position->UpdateVector2D(x, y); }

	Vector2D* GetPosition() { return _position; }

	float GetWidth() { return _collider_width; }
	float GetHeight() { return _collider_height; }

private:
	Vector2D* _position;
	float _collider_width;
	float _collider_height;
};

