#pragma once

class Vector2D
{
public:
	Vector2D() : _vector_x(0), _vector_y(0) {}
	Vector2D(float x, float y) : _vector_x(x), _vector_y(y) {}

	float X() { return _vector_x; }
	float Y() { return _vector_y; }

	// move the vector position by the provided x, y amount
	void MoveVectorPosition(float x, float y) { _vector_x += x; _vector_y += y; }

private:
	float _vector_x = 0;
	float _vector_y = 0;
};

