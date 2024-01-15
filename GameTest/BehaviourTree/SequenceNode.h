#pragma once
#include "IBehaviourNode.h"

class SequenceNode :
    public IBehaviourNode
{
public:
    SequenceNode(int id) : IBehaviourNode(id) {}

    bool CanHaveChildren() override { return true; }

    BehaviourNodeState AssessCurrState() override;
};

