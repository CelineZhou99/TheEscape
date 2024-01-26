#pragma once
#include "Actor.h"
#include "../UI/UI.h"


#define ITEM_COLLECT_SOUND ".\\Data\\Sounds\\ItemCollect.wav"

enum ItemType : uint8_t
{
	KEY,
    KEY_ESCAPE,
    GUMMY_BEAR,
};

class Item :
    public Actor
{
public:
    Item(unsigned short id, std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag, ItemType item_type)
        : Actor(id, renderer, pos_x, pos_y, tag), 
        _ui_icon(std::make_shared<UI>(GetRenderer()->GetFileName())),
        _quantity(1),
        _item_type(item_type) {}

    ItemType GetItemType() const { return _item_type; }
    short GetQuantity() const { return _quantity; }
    std::shared_ptr<UI> GetUIIcon() const { return _ui_icon; }

    void AddQuantity();
    void SubtractQuantity();

protected:
    std::shared_ptr<UI> _ui_icon;
    short _quantity;
    ItemType _item_type;
};

