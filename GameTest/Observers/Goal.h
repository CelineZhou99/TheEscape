#pragma once
#include "Publisher.h"
#include <string>

enum GoalType
{
    GOAL_PRESSURE_PLATE
};

class Goal :
    public Publisher
{
public:
    Goal(GoalType goal_type) : _goal_type(goal_type) {}

    bool IsGoalComplete();
    void IncrementContextCount();
    void DecrementContextCount();

    GoalType GetGoalType() { return _goal_type; }

protected:
    // count of the context that make up the goal e.g. 5 monsters to slay
    int _goal_context_count = 0;
    GoalType _goal_type;
};

