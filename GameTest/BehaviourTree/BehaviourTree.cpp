#include "stdafx.h"
#include "BehaviourTree.h"
#include "ActionNode.h"
#include "DecoratorNode.h"

unsigned short BehaviourTree::AllocateId()
{
	return _id++;
}

void BehaviourTree::AddActionNode(node_ptr parent, std::function<BehaviourNodeState()> action)
{
	parent->AddChild(std::make_shared<ActionNode>(AllocateId(), action));
}

std::shared_ptr<BehaviourNode> BehaviourTree::AddSelectorNode(node_ptr parent)
{
	std::shared_ptr<SelectorNode> selector = std::make_shared<SelectorNode>(AllocateId());
	parent->AddChild(selector);
	return selector;
}

std::shared_ptr<BehaviourNode> BehaviourTree::AddSequenceNode(node_ptr parent)
{
	std::shared_ptr<SequenceNode> sequence = std::make_shared<SequenceNode>(AllocateId());
	parent->AddChild(sequence);
	return sequence;
}

std::shared_ptr<BehaviourNode> BehaviourTree::AddDecoratorNode(node_ptr parent, std::vector<std::string> blackboard_variable_names, 
	Blackboard* blackboard)
{
	std::shared_ptr<DecoratorNode> decorator = std::make_shared<DecoratorNode>(AllocateId(), blackboard_variable_names, blackboard);
	parent->AddChild(decorator);
	return decorator;
}

void BehaviourTree::Update()
{
	// Run and evaluate tree and move active nodes
	// Run per tick
	_root->AssessCurrState();
}

