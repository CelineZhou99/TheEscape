#pragma once
#include "BehaviourNode.h"
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
			_root = std::make_shared<SelectorNode>(AllocateId());
		}
		else
		{
			_root = std::make_shared<SequenceNode>(AllocateId());
		}
	}

	node_ptr GetRoot() const { return _root; }

	unsigned short AllocateId();

	std::shared_ptr<Blackboard> GetBlackboard() const { return _blackboard; }

	void AddActionNode(node_ptr parent, std::function<BehaviourNodeState()> action);
	std::shared_ptr<BehaviourNode> AddSelectorNode(node_ptr parent);
	std::shared_ptr<BehaviourNode> AddSequenceNode(node_ptr parent);
	std::shared_ptr<BehaviourNode> AddDecoratorNode(node_ptr parent, std::vector<std::string> blackboard_variable_name, Blackboard* blackboard);

	void Update();

private:
	std::shared_ptr<Blackboard> _blackboard;
	node_ptr _root;
	unsigned short _id;
};

