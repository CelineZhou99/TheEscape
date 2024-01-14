#include "stdafx.h"
#include "SelectorNode.h"

BehaviourNodeState SelectorNode::AssessCurrState()
{
	// If one child succeeds, selector succeeds
	// If all child fails, selector fails
	if (_children.empty())
	{
		return BehaviourNodeState::UNDEFINED;
	}

	for (ptr child : _children)
	{
		if (child->AssessCurrState() == BehaviourNodeState::SUCCESS)
		{
			return BehaviourNodeState::SUCCESS;
		}
		else if (child->AssessCurrState() == BehaviourNodeState::RUNNING)
		{
			return BehaviourNodeState::RUNNING;
		}
	}

	return BehaviourNodeState::FAILED;
}
