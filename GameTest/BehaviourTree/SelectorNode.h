#pragma once
#include "IBehaviourNode.h"
class SelectorNode :
    public IBehaviourNode
{
public:
    SelectorNode(int id, ptr parent) : IBehaviourNode(id, parent) {}

    bool CanHaveChildren() override { return true; }

    BehaviourNodeState AssessCurrState() override;
};

