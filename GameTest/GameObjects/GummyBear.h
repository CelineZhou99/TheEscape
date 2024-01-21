#pragma once
#include "Item.h"
#include "IInteractable.h"

class World;

using Dialogue = std::vector<const char*>;

class GummyBear :
    public Item, public IInteractable
{
public:
    GummyBear(std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag, ItemType item_type) :
        Item(renderer, pos_x, pos_y, tag, item_type) 
    {
        _ui_icon->SetScale(0.5);
    }

    // TODO : THIS SHOULD BE IN THE ITEM CLASS? (iinteractable)
    void OnInteractWithPlayer(World& world) override;
};

