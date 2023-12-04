#pragma once
#include "Actor.h"
#include "PlayerState.h"
#include "PlayerStateIdle.h"

class Player :
    public Actor
{
    // context class for player states
public:
    Player(std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag) : Actor(renderer, pos_x, pos_y, tag) 
    {
        _player_state = std::make_shared<PlayerStateIdle>(this);
    }

    void SetState(std::shared_ptr<PlayerState> state);
    std::shared_ptr<PlayerState> GetState() { return _player_state; }

protected:
    std::shared_ptr<PlayerState> _player_state;
};

