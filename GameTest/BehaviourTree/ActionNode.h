#pragma once
#include "IBehaviourNode.h"
#include <functional>

class ActionNode :
    public IBehaviourNode
{
public:
    ActionNode(int id, ptr parent, std::function<BehaviourNodeState()> action) : IBehaviourNode(id, parent), _action(action) {}

    bool CanHaveChildren() override { return false; }

    BehaviourNodeState AssessCurrState() override;

private:
    std::function<BehaviourNodeState()> _action;
};

