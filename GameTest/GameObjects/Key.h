#pragma once
#include "Item.h"
#include "Player.h"
#include "../World.h"
#include "../Interactable.h"

enum KeyType
{
    ORDINARY,
    BOSS,
    ESCAPE,
};

class Key :
    public Item, public Interactable
{
public:
    Key(std::shared_ptr<Renderer> renderer, float pos_x, float pos_y, TagType tag, ItemType item_type, KeyType key_type)
        : Item(renderer, pos_x, pos_y, tag, item_type),
        _key_type(key_type)
    {
        _ui_icon->SetScale(0.5);
    }

    KeyType GetKeyType() { return _key_type; }
    
    // TODO: MAKE THIS INTO A VIRTUAL CLASS? (e.g. interactables (e.g. box, items))
    void OnInteractWithPlayer(World& world) override;

private:
    KeyType _key_type;
};

