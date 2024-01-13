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

	size_t children_has_succeeded = 0;

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
		else if (child->AssessCurrState() == BehaviourNodeState::SUCCESS)
		{
			++children_has_succeeded;
		}
	}

	return children_has_succeeded == GetNumOfChildren() ? BehaviourNodeState::SUCCESS : BehaviourNodeState::UNDEFINED;
}
