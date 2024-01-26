#pragma once
#include "../GameObjects/Vector2D.h"

class ColliderBase
{
	// abstract class as base for all types of colliders 
public:
	ColliderBase(Vector2D c_position, float width, float height) : 
		_position(c_position), _collider_width(width), _collider_height(height) {}
	
	// pure virtual function
	virtual bool CheckCollision(ColliderBase& obj_1_collider, ColliderBase& obj_2_collider) = 0;
	
	// move collider position by the provided x, y amount
	void MoveColliderPosition(float move_by_x, float move_by_y) { _position.MoveVectorPosition(move_by_x, move_by_y); }
	// set collider position to the provided x, y
	void SetColliderPosition(float x, float y) { _position.SetVectorPosition(x, y); }

	Vector2D GetPosition() const { return _position; }

	float GetWidth() const { return _collider_width; }
	float GetHeight() const { return _collider_height; }

protected:
	Vector2D _position;
	float _collider_width;
	float _collider_height;
};

