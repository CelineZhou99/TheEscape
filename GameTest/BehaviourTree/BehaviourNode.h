#pragma once
#include <vector>

enum BehaviourNodeState : uint8_t
{
	UNDEFINED,
	SUCCESS,
	RUNNING,
	FAILED,
};

class BehaviourNode;
class ServiceNode;

using node_ptr = std::shared_ptr<BehaviourNode>;

class BehaviourNode
{
public:
	BehaviourNode(unsigned short id) : 
		_children({}), _service(nullptr), _id(id), _state(BehaviourNodeState::UNDEFINED) {}

	unsigned short GetId() { return _id; }

	void AddChild(node_ptr child);
	size_t GetNumOfChildren() const { return _children.size(); }

	BehaviourNodeState GetState() const { return _state; }
	void SetState(BehaviourNodeState state) { _state = state; }

	void SetService(node_ptr service);

	virtual bool CanHaveChildren() const = 0;
	virtual bool CanAttachService() const = 0;
	
	virtual BehaviourNodeState AssessCurrState() = 0;

protected:
	std::vector<node_ptr> _children;
	node_ptr _service;
	unsigned short _id;
	BehaviourNodeState _state;
};

