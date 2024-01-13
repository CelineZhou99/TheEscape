#pragma once
#include <vector>
#include <memory>

enum BehaviourNodeState : uint8_t
{
	UNDEFINED,
	SUCCESS,
	RUNNING,
	FAILED,
};

class IBehaviourNode;

using ptr = std::shared_ptr<IBehaviourNode>;

class IBehaviourNode
{
public:
	IBehaviourNode(int id, ptr parent) : _id(id), _parent(parent), _children({}), _state(BehaviourNodeState::UNDEFINED) {}

	int GetId() { return _id; }

	ptr GetParent() { return _parent; }

	ptr GetChild(int index);
	void AddChild(ptr child);
	size_t GetNumOfChildren() { return _children.size(); }

	BehaviourNodeState GetState() { return _state; }

	virtual bool CanHaveChildren() = 0;
	
	virtual BehaviourNodeState AssessCurrState() = 0;

protected:
	int _id;
	ptr _parent;
	std::vector<ptr> _children;
	BehaviourNodeState _state;
};

