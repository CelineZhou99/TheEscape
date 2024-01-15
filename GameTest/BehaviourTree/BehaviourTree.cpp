#include "stdafx.h"
#include "BehaviourTree.h"

int BehaviourTree::AllocateId()
{
	return _id++;
}

void BehaviourTree::AddActionNode(ptr parent, std::function<BehaviourNodeState()> action)
{
	parent->AddChild(std::make_shared<ActionNode>(AllocateId(), action));
}

void BehaviourTree::AddSelectorNode(ptr parent)
{
	parent->AddChild(std::make_shared<SelectorNode>(AllocateId()));
}

void BehaviourTree::AddSequenceNode(ptr parent)
{
	parent->AddChild(std::make_shared<SequenceNode>(AllocateId()));
}


void BehaviourTree::Update()
{
	// Run and evaluate tree and move active nodes
	// Run per tick
	_root->AssessCurrState();
}

