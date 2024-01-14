#pragma once
#include "IBehaviourNode.h"
#include "SequenceNode.h"
#include "SelectorNode.h"
#include "ActionNode.h"

// TODO: MAYBE FORWARD DECLARE ALL THE H FILES AND MOVE THEM TO THE CPP FILE INSTEAD?

enum RootNodeType : uint8_t
{
	SELECTOR,
	SEQUENCE,
};

class BehaviourTree
{
public:
	BehaviourTree(RootNodeType root_node_type)
	{
		_id = 0;
		if (root_node_type == RootNodeType::SELECTOR)
		{
			_root = std::make_shared<SelectorNode>(_id, nullptr);
		}
		else
		{
			_root = std::make_shared<SequenceNode>(_id, nullptr);
		}
		++_id;
	}

	ptr GetRoot() { return _root; }

	void AddActionNode(ptr parent, std::function<BehaviourNodeState()> action);
	void AddSelectorNode(ptr parent);
	void AddSequenceNode(ptr parent);

	void Update();

private:
	ptr _root;
	int _id;
};

