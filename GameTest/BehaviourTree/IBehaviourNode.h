#pragma once
#include <vector>

enum BehaviourNodeState : uint8_t
{
	UNDEFINED,
	SUCCESS,
	RUNNING,
	FAILED,
};

class IBehaviourNode;

using node_ptr = std::shared_ptr<IBehaviourNode>;

class IBehaviourNode
{
public:
	IBehaviourNode(unsigned short id) : 
		_children({}), _id(id), _state(BehaviourNodeState::UNDEFINED) {}

	unsigned short GetId() { return _id; }

	void AddChild(node_ptr child);
	size_t GetNumOfChildren() { return _children.size(); }

	BehaviourNodeState GetState() { return _state; }
	void SetState(BehaviourNodeState state) { _state = state; }

	virtual bool CanHaveChildren() = 0;
	
	virtual BehaviourNodeState AssessCurrState() = 0;

protected:
	std::vector<node_ptr> _children;
	unsigned short _id;
	BehaviourNodeState _state;
};

