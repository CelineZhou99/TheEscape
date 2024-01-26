#pragma once
#include "BehaviourNode.h"
#include <functional>

class ActionNode :
    public BehaviourNode
{
public:
    ActionNode(unsigned short id, std::function<BehaviourNodeState()> action) : 
        BehaviourNode(id), _action(action) {}

    bool CanHaveChildren() const override { return false; }
    bool CanAttachService() const override { return true; }

    BehaviourNodeState AssessCurrState() override;

private:
    std::function<BehaviourNodeState()> _action;
};

