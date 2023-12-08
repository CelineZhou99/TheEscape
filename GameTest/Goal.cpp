#include "stdafx.h"
#include "Goal.h"

bool Goal::IsGoalComplete()
{
	if (_goal_context_count <= 0)
	{
		return true;
	}
	return false;
}

void Goal::IncrementContextCount()
{
	_goal_context_count++;
}

void Goal::DecrementContextCount()
{
	_goal_context_count--;
}
