#pragma once
#include "BehaviourNode.h"
#include "Blackboard.h"

class DecoratorNode :
    public BehaviourNode
{
public:
    // default decorator node will check for whether blackboard values are valid
    DecoratorNode(unsigned short id, std::vector<std::string> blackboard_variable_names, Blackboard* blackboard) :
        BehaviourNode(id), 
        _blackboard_variable_names(blackboard_variable_names), 
        _blackboard(blackboard) {}

    bool CanHaveChildren() const override { return true; }
    bool CanAttachService() const override { return false; }

    BehaviourNodeState AssessCurrState() override;

private:
    std::vector<std::string> _blackboard_variable_names;
    Blackboard* _blackboard;
};

