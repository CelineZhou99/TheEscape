#pragma once
#include "GameObjects/Item.h"

class Inventory
{
public:
	std::vector<std::shared_ptr<Item>> GetItemList() { return _item_list; }

	void AddToInventory(Item* item);
	void RemoveFromInventory(Item* item);
	Item* FindInInventory(ItemType item_type);

private:
	std::vector<std::shared_ptr<Item>> _item_list = {};
};

