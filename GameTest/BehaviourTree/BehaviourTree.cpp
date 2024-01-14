#include "stdafx.h"
#include "BehaviourTree.h"

void BehaviourTree::AddActionNode(ptr parent, std::function<BehaviourNodeState()> action)
{
	parent->AddChild(std::make_shared<ActionNode>(_id, parent, action));
	++_id;
}

void BehaviourTree::AddSelectorNode(ptr parent)
{
	parent->AddChild(std::make_shared<SelectorNode>(_id, parent));
	++_id;
}

void BehaviourTree::AddSequenceNode(ptr parent)
{
	parent->AddChild(std::make_shared<SequenceNode>(_id, parent));
	++_id;
}

void BehaviourTree::Update()
{
	// Run and evaluate tree and move active nodes
	// Run per tick
	_root->AssessCurrState();
}

