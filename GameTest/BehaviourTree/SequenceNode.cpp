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

	for (ptr child : _children)
	{
		if (child->AssessCurrState() == BehaviourNodeState::FAILED)
		{
			return BehaviourNodeState::FAILED;
		}
		else if (child->AssessCurrState() == BehaviourNodeState::RUNNING)
		{
			return BehaviourNodeState::RUNNING;
		}
	}

	return BehaviourNodeState::SUCCESS;
}
