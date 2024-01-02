#pragma once
#include "Actor.h"
#include "../UI.h"

enum ItemType
{
	KEY,
    SWORD,
    POTION,
};

class Item :
    public Actor
{
public:
    Item(std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag, ItemType item_type) 
        : Actor(renderer, pos_x, pos_y, tag), 
        _item_type(item_type),
        _ui_icon(std::make_shared<UI>(GetRenderer()->GetFileName())) {}

    ItemType GetItemType() { return _item_type; }
    int GetQuantity() { return _quantity; }
    std::shared_ptr<UI> GetUIIcon() { return _ui_icon; }

    void AddQuantity();
    void SubtractQuantity();

protected:
    ItemType _item_type;
    int _quantity = 1;
    std::shared_ptr<UI> _ui_icon;
};

