#include "stdafx.h"
#include "DecoratorNode.h"

BehaviourNodeState DecoratorNode::AssessCurrState()
{
    // decorator can only have one child
    if (_children.empty() || _children.size() > 1 || _blackboard_variable_names.empty())
    {
        return BehaviourNodeState::UNDEFINED;
    }

    for (std::string name : _blackboard_variable_names)
    {
        if (!_blackboard->GetVariable(name))
        {
            return BehaviourNodeState::FAILED;
        }
    }

    if (_service)
    {
        _service->AssessCurrState();
    }
    BehaviourNodeState child_state = _children[0]->AssessCurrState();
    return child_state;
}
