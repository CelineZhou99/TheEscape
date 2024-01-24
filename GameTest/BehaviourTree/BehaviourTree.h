#pragma once
#include "IBehaviourNode.h"
#include "SequenceNode.h"
#include "SelectorNode.h"
#include "Blackboard.h"
#include <functional>

class Blackboard;

enum RootNodeType : uint8_t
{
	SELECTOR,
	SEQUENCE,
};

class BehaviourTree
{
public:
	BehaviourTree(RootNodeType root_node_type) : _blackboard(std::make_shared<Blackboard>())
	{
		_id = 0;
		if (root_node_type == RootNodeType::SELECTOR)
		{
			_root = std::make_shared<SelectorNode>(_id);
		}
		else
		{
			_root = std::make_shared<SequenceNode>(_id);
		}
		++_id;
	}

	node_ptr GetRoot() { return _root; }

	unsigned short AllocateId();

	std::shared_ptr<Blackboard> GetBlackboard() { return _blackboard; }

	void AddActionNode(node_ptr parent, std::function<BehaviourNodeState()> action);
	std::shared_ptr<IBehaviourNode> AddSelectorNode(node_ptr parent);
	std::shared_ptr<IBehaviourNode> AddSequenceNode(node_ptr parent);
	std::shared_ptr<IBehaviourNode> AddDecoratorNode(node_ptr parent, std::string blackboard_variable_name, Blackboard* blackboard);

	void Update();

private:
	std::shared_ptr<Blackboard> _blackboard;
	node_ptr _root;
	unsigned short _id;
};

