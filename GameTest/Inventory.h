#pragma once
#include "GameObjects/Item.h"

class Inventory
{
public:
	void AddToInventory(Item* item);
	void RemoveFromInventory(Item* item);
	std::vector<std::shared_ptr<Item>> GetItemList() { return _item_list; }

private:
	std::vector<std::shared_ptr<Item>> _item_list = {};
};

