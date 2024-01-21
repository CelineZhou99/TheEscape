#pragma once
#include "IBehaviourNode.h"
#include <functional>

class ActionNode :
    public IBehaviourNode
{
public:
    ActionNode(unsigned short id, std::function<BehaviourNodeState()> action) : IBehaviourNode(id), _action(action) {}

    bool CanHaveChildren() override { return false; }

    BehaviourNodeState AssessCurrState() override;

private:
    std::function<BehaviourNodeState()> _action;
};

