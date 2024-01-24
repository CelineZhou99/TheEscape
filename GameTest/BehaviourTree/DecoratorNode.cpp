#include "stdafx.h"
#include "DecoratorNode.h"

BehaviourNodeState DecoratorNode::AssessCurrState()
{
    // decorator can only have one child
    if (_children.empty() || _children.size() > 1 || _blackboard_variable_name.empty())
    {
        return BehaviourNodeState::UNDEFINED;
    }

    if (_blackboard->GetVariable(_blackboard_variable_name))
    {
        BehaviourNodeState child_state = _children[0]->AssessCurrState();
        return child_state;
    }
    else
    {
        return BehaviourNodeState::FAILED;
    }
}
