#include "stdafx.h"
#include "IBehaviourNode.h"

ptr IBehaviourNode::GetChild(int index)
{
	if (index < _children.size())
	{
		return _children[index];
	}
	return nullptr;
}

void IBehaviourNode::AddChild(ptr child)
{
	if (CanHaveChildren())
	{
		_children.push_back(child);
	}
}
