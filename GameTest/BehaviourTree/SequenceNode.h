#pragma once
#include "IBehaviourNode.h"

class SequenceNode :
    public IBehaviourNode
{
public:
    SequenceNode(int id, ptr parent) : IBehaviourNode(id, parent) {}

    bool CanHaveChildren() override { return true; }

    BehaviourNodeState AssessCurrState() override;
};

