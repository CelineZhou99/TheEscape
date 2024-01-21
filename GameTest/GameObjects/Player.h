#pragma once
#include "Actor.h"
#include "../States/PlayerStateIdle.h"
#include "../States/PlayerStateWalk.h"
#include "Inventory.h"
#include "IHealthSystem.h"
#include <unordered_map>

#define IMAGE_HEART ".\\Data\\Images\\Heart.bmp"
#define IMAGE_PLAYER_IDLE ".\\Data\\Images\\IdleAnimationS.bmp"
#define IMAGE_PLAYER_WALK ".\\Data\\Images\\WalkAnimationS.bmp"

using PlayerStateMap = std::unordered_map<PlayerStateType, std::shared_ptr<IPlayerState>>;
using Dialogue = std::vector<const char*>;

class World;

class Player :
    public Actor, public IHealthSystem
{
    // context class for player states
public:
    Player(std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag) :
        Actor(renderer, pos_x, pos_y, tag),
        _player_state_map({
            {PlayerStateType::IDLE, std::make_shared<PlayerStateIdle>(this)},
            {PlayerStateType::WALK, std::make_shared<PlayerStateWalk>(this)}
            }),
        _enable_shoot_dialogue({
            "Oh a gummy bear, Yum!",
            "*NomNom*", "...",
            "Oh god why is it so spicy??!!",
            "Uh oh...",
            "My stomach feels like its on fire...",
            "[You have unlocked a new ability.]",
            "[Use I, K, J, L, to shoot.]"
        }),
        _inventory(std::make_shared<Inventory>()),
        _health_icon(std::make_shared<UI>(IMAGE_HEART)),
        _is_invulnerable(false),
        _can_shoot(false),
        _last_facing_direction(FacingDirection::DOWN),
        _state_type(PlayerStateType::IDLE)
    {
        SetMaxHealth(5);
    }

    PlayerStateType GetStateType() { return _state_type; }
    void SetState(PlayerStateType state);

    FacingDirection GetLastFacingDirection() { return _last_facing_direction; }
    void SetLastFacingDirection(FacingDirection direction) { _last_facing_direction = direction; }

    std::shared_ptr<Inventory> GetInventory() { return _inventory; }

    void TakeDamage() override;

    std::shared_ptr<UI> GetHealthIcon() { return _health_icon; }

    bool GetIsInvulnerable() { return _is_invulnerable; }
    void SetIsInvulnerable(bool is_invulnerable) { _is_invulnerable = is_invulnerable; }

    bool GetCanShoot() { return _can_shoot; }
    void SetCanShoot(World& world);

protected:
    PlayerStateMap _player_state_map;
    Dialogue _enable_shoot_dialogue;
    std::shared_ptr<Inventory> _inventory;
    std::shared_ptr<UI> _health_icon;
    bool _is_invulnerable;
    bool _can_shoot;
    FacingDirection _last_facing_direction;
    PlayerStateType _state_type;
};

