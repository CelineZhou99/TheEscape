#pragma once

class Vector2D
{
public:
	Vector2D(float x, float y)
	{
		_vector_x = x;
		_vector_y = y;
	}

	float X() { return _vector_x; }
	float Y() { return _vector_y; }

	void UpdateVector2D(float x, float y) { _vector_x += x; _vector_y += y; }

private:
	float _vector_x;
	float _vector_y;
};

