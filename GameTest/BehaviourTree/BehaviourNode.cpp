#include "stdafx.h"
#include "BehaviourNode.h"

void BehaviourNode::AddChild(node_ptr child)
{
	if (CanHaveChildren())
	{
		_children.push_back(child);
	}
}

void BehaviourNode::SetService(node_ptr service)
{
	if (CanAttachService())
	{
		_service = service;
	}
}
