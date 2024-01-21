#pragma once
#include "IBehaviourNode.h"

class SelectorNode :
    public IBehaviourNode
{
public:
    SelectorNode(unsigned short id) : IBehaviourNode(id) {}

    bool CanHaveChildren() override { return true; }

    BehaviourNodeState AssessCurrState() override;
};

