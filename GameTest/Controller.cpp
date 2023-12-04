#include "stdafx.h"
#include "Controller.h"

bool Controller::IsMoving()
{
	if (_speed > 0)
	{
		return true;
	}
	return false;
}
