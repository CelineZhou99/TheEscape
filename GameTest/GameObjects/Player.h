#pragma once
#include "Actor.h"
#include "../States/PlayerState.h"
#include "../States/PlayerStateIdle.h"
#include "../States/PlayerStateWalk.h"
#include <unordered_map>

using PlayerStateMap = std::unordered_map<PlayerStateType, std::shared_ptr<PlayerState>>;

class Player :
    public Actor
{
    // context class for player states
public:
    Player(std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag) : Actor(renderer, pos_x, pos_y, tag), _state_type(PlayerStateType::IDLE)
    {
        std::shared_ptr<PlayerStateIdle> player_state_idle = std::make_shared<PlayerStateIdle>(this);
        std::shared_ptr<PlayerStateWalk> player_state_walk = std::make_shared<PlayerStateWalk>(this);
        _player_state_map[PlayerStateType::IDLE] = player_state_idle;
        _player_state_map[PlayerStateType::WALK] = player_state_walk;
    }

    void SetState(PlayerStateType state);
    PlayerStateType GetStateType() { return _state_type; }

protected:
    PlayerStateMap _player_state_map;
    PlayerStateType _state_type;
};

