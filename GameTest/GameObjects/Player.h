#pragma once
#include "Actor.h"
#include "../States/PlayerStateIdle.h"
#include "../States/PlayerStateWalk.h"
#include "Inventory.h"
#include "HealthComponent.h"
#include <unordered_map>

#define IMAGE_HEART ".\\Data\\Images\\Heart.bmp"
#define IMAGE_PLAYER_IDLE ".\\Data\\Images\\IdleAnimationS.bmp"
#define IMAGE_PLAYER_WALK ".\\Data\\Images\\WalkAnimationS.bmp"
#define HURT_SOUND ".\\Data\\Sounds\\Hurt.wav"

using PlayerStateMap = std::unordered_map<PlayerStateType, std::shared_ptr<IPlayerState>>;
using Dialogue = std::vector<std::string>;

class World;
class Scene;

class Player :
    public Actor
{
    // context class for player states
public:
    Player(unsigned short id, std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag, HealthComponentPtr health_component) :
        Actor(id, renderer, pos_x, pos_y, tag, health_component),
        _player_state_map({
            {PlayerStateType::IDLE, std::make_shared<PlayerStateIdle>(this)},
            {PlayerStateType::WALK, std::make_shared<PlayerStateWalk>(this)}
            }),
        _enable_shoot_dialogue({
            "Oh a gummy bear, yum!",
            "*Nom*", 
            "...",
            "Oh god why is it so spicy??!!",
            "*Stomach growls*",
            "Uh oh...",
            "My stomach... feels like its on fire...",
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
        SetSpeed(2.f);
    }

    PlayerStateType GetStateType() const { return _state_type; }
    void SetState(PlayerStateType state);

    FacingDirection GetLastFacingDirection() const { return _last_facing_direction; }
    void SetLastFacingDirection(FacingDirection direction) { _last_facing_direction = direction; }

    std::shared_ptr<Inventory> GetInventory() const { return _inventory; }

    void TakeDamage();

    std::shared_ptr<UI> GetHealthIcon() const { return _health_icon; }

    bool GetIsInvulnerable() const { return _is_invulnerable; }
    void SetIsInvulnerable(bool is_invulnerable) { _is_invulnerable = is_invulnerable; }

    bool GetCanShoot() const { return _can_shoot; }
    void SetCanShoot(World& world);

    void Update(float deltaTime, bool player_requested_move, bool player_will_move, FacingDirection direction, float player_move_by_x, float player_move_by_y);

    void InvulnerabilityCountdown(float deltaTime);

    void SetPlayerColour();

protected:
    PlayerStateMap _player_state_map;
    Dialogue _enable_shoot_dialogue;
    std::shared_ptr<Inventory> _inventory;
    std::shared_ptr<UI> _health_icon;
    float start_timer = 0.f;
    float stop_timer = 2.f;
    bool _is_invulnerable;
    bool _can_shoot;
    FacingDirection _last_facing_direction;
    PlayerStateType _state_type;
};

