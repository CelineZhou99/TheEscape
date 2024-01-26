#pragma once
#include "Actor.h"
#include "IInteractable.h"

class ResetButton :
    public Actor, public IInteractable
{
public:
    ResetButton(unsigned short id, std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag) :
        Actor(id, renderer, pos_x, pos_y, tag), _original_box_locations({}), _original_goal_context_count(0), _is_disabled(false) {}

    void OnInteractWithPlayer(World& world) override;

    void AddToOriginalBoxLocation(Vector2D& location);

    unsigned short GetOriginalGoalContextCount() const { return _original_goal_context_count; }
    void SetOriginalGoalContextCount(unsigned short count) { _original_goal_context_count = count; }

    void SetIsDisabled(bool is_disabled) { _is_disabled = is_disabled; }

private:
    std::vector<Vector2D> _original_box_locations;
    unsigned short _original_goal_context_count;
    bool _is_disabled;
};

