#include "stdafx.h"
#include "DecoratorNode.h"

template <typename T>
BehaviourNodeState DecoratorNode<T>::AssessCurrState()
{
    // decorator can only have one child
    if (_children.empty() || _children.size() > 1)
    {
        return BehaviourNodeState::UNDEFINED;
    }

    if (_value_to_assess == _supposed_value)
    {
        BehaviourNodeState child_state = _children[0]->AssessCurrState();
        return child_state;
    }
    else
    {
        return BehaviourNodeState::FAILED;
    }
}
