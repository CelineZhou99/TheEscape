#pragma once
#include "Actor.h"
#include "../States/PlayerState.h"
#include "../States/PlayerStateIdle.h"
#include "../States/PlayerStateWalk.h"
#include "../Inventory.h"
#include <unordered_map>

#define IMAGE_HEART ".\\Data\\Images\\Heart.bmp"

using PlayerStateMap = std::unordered_map<PlayerStateType, std::shared_ptr<PlayerState>>;

class Player :
    public Actor
{
    // context class for player states
public:
    Player(std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag) : 
        Actor(renderer, pos_x, pos_y, tag), 
        _player_state_map({
            {PlayerStateType::IDLE, std::make_shared<PlayerStateIdle>(this)},
            {PlayerStateType::WALK, std::make_shared<PlayerStateWalk>(this)}
            }),
        _state_type(PlayerStateType::IDLE),
        _inventory(std::make_shared<Inventory>()),
        _health_icon(std::make_shared<UI>(IMAGE_HEART))
    {}

    PlayerStateType GetStateType() { return _state_type; }
    void SetState(PlayerStateType state);

    std::shared_ptr<Inventory> GetInventory() { return _inventory; }

    int GetHealth() { return _health; }

    std::shared_ptr<UI> GetHealthIcon() { return _health_icon; }

protected:
    PlayerStateMap _player_state_map;
    PlayerStateType _state_type;
    std::shared_ptr<Inventory> _inventory;
    int _health = 3;
    std::shared_ptr<UI> _health_icon;
};

