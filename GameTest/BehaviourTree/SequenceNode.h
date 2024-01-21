#pragma once
#include "IBehaviourNode.h"

class SequenceNode :
    public IBehaviourNode
{
public:
    SequenceNode(unsigned short id) : IBehaviourNode(id) {}

    bool CanHaveChildren() override { return true; }

    BehaviourNodeState AssessCurrState() override;
};

