#pragma once
#include "Item.h"
#include "Player.h"
#include "../World.h"
#include "Interactable.h"

class Key :
    public Item, public Interactable
{
public:
    Key(std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag, ItemType item_type)
        : Item(renderer, pos_x, pos_y, tag, item_type)
    {
        _ui_icon->SetScale(0.5);
    }
    
    void OnInteractWithPlayer(World& world) override;
};

