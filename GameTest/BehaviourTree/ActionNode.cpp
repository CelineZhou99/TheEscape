#include "stdafx.h"
#include "ActionNode.h"

BehaviourNodeState ActionNode::AssessCurrState()
{
	// since action is a function that returns BehaviourState
	// the state will be determined by the action function
	if (_action)
	{
		if (_service)
		{
			_service->AssessCurrState();
		}
		return _action();
	}
	return BehaviourNodeState::UNDEFINED;
}