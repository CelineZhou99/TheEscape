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
	IBehaviourNode(int id) : 
		_id(id), _children({}), _state(BehaviourNodeState::UNDEFINED) {}

	int GetId() { return _id; }

	ptr GetChild(int index);
	void AddChild(ptr child);
	size_t GetNumOfChildren() { return _children.size(); }

	BehaviourNodeState GetState() { return _state; }
	void SetState(BehaviourNodeState state) { _state = state; }

	virtual bool CanHaveChildren() = 0;
	
	virtual BehaviourNodeState AssessCurrState() = 0;

	bool operator == (const IBehaviourNode& node) 
	{
		if (_id == node._id)
		{
			return true;
		}
		return false;
	}

protected:
	int _id;
	std::vector<ptr> _children;
	BehaviourNodeState _state;
};

