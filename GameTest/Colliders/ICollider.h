#pragma once
#include "../GameObjects/Vector2D.h"

class ICollider
{
	// abstract class as base for all types of colliders 
public:
	ICollider(Vector2D c_position, float width, float height) : 
		_position(c_position), _collider_width(width), _collider_height(height) {}
	
	// pure virtual function
	virtual bool CheckCollision(ICollider& obj_1_collider, ICollider& obj_2_collider) = 0;
	
	// move collider position by the provided x, y amount
	void MoveColliderPosition(float move_by_x, float move_by_y) { _position.MoveVectorPosition(move_by_x, move_by_y); }
	// set collider position to the provided x, y
	void SetColliderPosition(float x, float y) { _position.SetVectorPosition(x, y); }

	Vector2D GetPosition() { return _position; }

	float GetWidth() { return _collider_width; }
	float GetHeight() { return _collider_height; }

protected:
	Vector2D _position;
	float _collider_width;
	float _collider_height;
};

