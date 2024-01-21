#pragma once
#include "Publisher.h"

class Scene;
class GameObject;

enum GoalType : uint8_t
{
    GOAL_NONE,
    GOAL_PRESSURE_PLATE,
    GOAL_SLIME,
};

class Goal :
    public Publisher
{
public:
    Goal() : _goal_context_count(0), _goal_type(GoalType::GOAL_NONE), _goal_reward(""), _goal_reward_tile(nullptr) {}

    bool IsGoalComplete();
    short GetContextCount() { return _goal_context_count; }
    void SetContextCount(short count) { _goal_context_count = count; }
    void IncrementContextCount();
    void DecrementContextCount();
    void SpawnReward(Scene* scene);

    GoalType GetGoalType() { return _goal_type; }
    void SetGoalType(GoalType goal_type) { _goal_type = goal_type; }

    void SetGoalReward(std::string goal_reward) { _goal_reward = goal_reward; }

    void SetGoalRewardTile(GameObject* goal_reward_tile) { _goal_reward_tile = goal_reward_tile; }

protected:
    // count of the context that make up the goal e.g. 5 monsters to slay
    std::string _goal_reward;
    GameObject* _goal_reward_tile;
    short _goal_context_count;
    GoalType _goal_type;
};

