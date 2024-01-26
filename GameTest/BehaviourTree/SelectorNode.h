#pragma once
#include "BehaviourNode.h"

class SelectorNode :
    public BehaviourNode
{
public:
    SelectorNode(unsigned short id) : BehaviourNode(id) {}

    bool CanHaveChildren() const override { return true; }
    bool CanAttachService() const override { return true; }

    BehaviourNodeState AssessCurrState() override;

};

