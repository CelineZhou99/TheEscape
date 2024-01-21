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

	for (node_ptr child : _children)
	{
		BehaviourNodeState child_state = child->AssessCurrState();
		if (child_state == BehaviourNodeState::SUCCESS)
		{
			return BehaviourNodeState::SUCCESS;
		}
		else if (child_state == BehaviourNodeState::RUNNING)
		{
			return BehaviourNodeState::RUNNING;
		}
	}

	return BehaviourNodeState::FAILED;
}
