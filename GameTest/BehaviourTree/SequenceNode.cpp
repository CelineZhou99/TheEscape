#include "stdafx.h"
#include "SequenceNode.h"

BehaviourNodeState SequenceNode::AssessCurrState()
{
	// If one children fails, sequence fails
	// If all children succeeds, sequence succeeds
	if (_children.empty())
	{
		return BehaviourNodeState::UNDEFINED;
	}

	if (_service)
	{
		_service->AssessCurrState();
	}

	for (node_ptr child : _children)
	{
		BehaviourNodeState child_state = child->AssessCurrState();
		if (child_state == BehaviourNodeState::FAILED)
		{
			return BehaviourNodeState::FAILED;
		}
		else if (child_state == BehaviourNodeState::RUNNING)
		{
			return BehaviourNodeState::RUNNING;
		}
	}
	return BehaviourNodeState::SUCCESS;
}
