#include "stdafx.h"
#include "Inventory.h"

void Inventory::AddToInventory(Item& item)
{
	// TODO: FINDING DOES NOT WORK ATM - SAME ISSUE AS SCENE.CPP LINE 28
	std::vector<std::shared_ptr<Item>>::iterator it = std::find(_item_list.begin(), _item_list.end(), std::make_shared<Item>(item));

	if (it != _item_list.end())
	{
		it->get()->AddQuantity();
	}
	else
	{
		_item_list.push_back(std::make_shared<Item>(item));
	}
}

void Inventory::RemoveFromInventory(Item& item)
{
	// TODO: FINDING DOES NOT WORK ATM - SAME ISSUE AS SCENE.CPP LINE 28
	std::vector<std::shared_ptr<Item>>::iterator it = std::find(_item_list.begin(), _item_list.end(), std::make_shared<Item>(item));

	if (it != _item_list.end())
	{
		if (it->get()->GetQuantity() > 1)
		{
			it->get()->SubtractQuantity();
		}
	}
	else
	{
		_item_list.erase(it);
	}
}