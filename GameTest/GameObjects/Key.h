#pragma once
#include "Item.h"
#include "IInteractable.h"

class World;

class Key :
    public Item, public IInteractable
{
public:
    Key(unsigned short id, std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag, ItemType item_type)
        : Item(id, renderer, pos_x, pos_y, tag, item_type)
    {
        _ui_icon->SetScale(0.5);
    }
    
    void OnInteractWithPlayer(World& world) override;
};

