#pragma once
#include "IBehaviourNode.h"
class SelectorNode :
    public IBehaviourNode
{
public:
    SelectorNode(int id) : IBehaviourNode(id) {}

    bool CanHaveChildren() override { return true; }

    BehaviourNodeState AssessCurrState() override;
};

