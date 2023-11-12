#include "stdafx.h"
#include "Actor.h"
#include "App/app.h"

bool Actor::IsMoving()
{
	bool is_moving = false;

	if (App::IsKeyPressed('W') || App::IsKeyPressed('S') || App::IsKeyPressed('A') || App::IsKeyPressed('D'))
	{
		is_moving = true;
	}

	return is_moving;
}
