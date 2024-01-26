#pragma once
#include "Publisher.h"

#define GOAL_COMPLETE_SOUND ".\\Data\\Sounds\\Success.wav"

class Scene;
class GameObject;
class World;
class Item;

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
    Goal(World& world) : _goal_context_count(0), _goal_type(GoalType::GOAL_NONE), _goal_reward(""), _goal_reward_tile(nullptr), _world(world) {}

    bool IsGoalComplete();
    short GetContextCount() const { return _goal_context_count; }
    void SetContextCount(short count) { _goal_context_count = count; }
    void IncrementContextCount();
    void DecrementContextCount();
    void SpawnReward(Scene* scene, const char* map_file_name);

    GoalType GetGoalType() const { return _goal_type; }
    void SetGoalType(GoalType goal_type) { _goal_type = goal_type; }

    void SetGoalReward(std::string goal_reward) { _goal_reward = goal_reward; }

    void SetGoalRewardTile(GameObject* goal_reward_tile) { _goal_reward_tile = goal_reward_tile; }

    void AddToUnlockedDoors(unsigned short id);
    bool FindInUnlockedDoors(unsigned short id);

    std::shared_ptr<Item> FindInSpawnedRewards(const char* file_name);

protected:
    // count of the context that make up the goal e.g. 5 monsters to slay
    std::string _goal_reward;
    GameObject* _goal_reward_tile;
    World& _world;
    short _goal_context_count;
    GoalType _goal_type;
};

