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

	size_t children_has_failed = 0;

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
		else if (child->AssessCurrState() == BehaviourNodeState::FAILED)
		{
			++children_has_failed;
		}
	}

	return children_has_failed == GetNumOfChildren() ? BehaviourNodeState::FAILED : BehaviourNodeState::UNDEFINED;
}
