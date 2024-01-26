#pragma once
#include "BehaviourNode.h"

class SequenceNode :
    public BehaviourNode
{
public:
    SequenceNode(unsigned short id) : BehaviourNode(id) {}

    bool CanHaveChildren() const override { return true; }
    bool CanAttachService() const override { return true; }

    BehaviourNodeState AssessCurrState() override;

};

