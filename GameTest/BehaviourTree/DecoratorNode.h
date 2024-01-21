#pragma once
#include "IBehaviourNode.h"

template <typename T>
class DecoratorNode :
    public IBehaviourNode
{
public:
    // template value since decorators can assess different types of values
    DecoratorNode(unsigned short id, T value_to_assess, T supposed_value) : 
        IBehaviourNode(id), _value_to_assess(value_to_assess), _supposed_value(supposed_value) {}

    void SetValueToAssess(const T& value_to_assess) { _value_to_assess = value_to_assess; }

    bool CanHaveChildren() override { return true; }

    BehaviourNodeState AssessCurrState() override;

private:
    T _value_to_assess;
    T _supposed_value;
};

