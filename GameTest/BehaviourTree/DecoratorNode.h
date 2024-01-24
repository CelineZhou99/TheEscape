#pragma once
#include "IBehaviourNode.h"
#include "Blackboard.h"

class DecoratorNode :
    public IBehaviourNode
{
public:
    // default decorator node will check for whether blackboard values are valid
    DecoratorNode(unsigned short id, std::string blackboard_variable_name, Blackboard* blackboard) :
        IBehaviourNode(id), 
        _blackboard_variable_name(blackboard_variable_name), 
        _blackboard(blackboard) {}

    bool CanHaveChildren() override { return true; }

    BehaviourNodeState AssessCurrState() override;

private:
    std::string _blackboard_variable_name;
    Blackboard* _blackboard;
};

