#include "stdafx.h"
#include "IBehaviourNode.h"

void IBehaviourNode::AddChild(node_ptr child)
{
	if (CanHaveChildren())
	{
		_children.push_back(child);
	}
}
