#pragma once
#include "Publisher.h"
#include <string>

enum GoalType
{
    GOAL_NONE,
    GOAL_PRESSURE_PLATE,
};

class Goal :
    public Publisher
{
public:
    Goal() : _goal_context_count(0), _goal_type(GoalType::GOAL_NONE) {}

    bool IsGoalComplete();
    void IncrementContextCount();
    void DecrementContextCount();

    GoalType GetGoalType() { return _goal_type; }
    void SetGoalType(GoalType goal_type) { _goal_type = goal_type; }

protected:
    // count of the context that make up the goal e.g. 5 monsters to slay
    int _goal_context_count;
    GoalType _goal_type;
};

