#include "stdafx.h"
#include "Inventory.h"
#include "GameObjects/Key.h"

void Inventory::AddToInventory(Item* item)
{
	std::vector<std::shared_ptr<Item>>::iterator it = 
		std::find_if(_item_list.begin(), _item_list.end(), [item](const std::shared_ptr<Item>& i)
		{
			if (i->GetItemType() == item->GetItemType())
			{
				if (item->GetItemType() == ItemType::KEY)
				{
					Key& item_key = static_cast<Key&>(*item);
					Key& i_key = static_cast<Key&>(*i.get());
					if (item_key.GetKeyType() == i_key.GetKeyType())
					{
						return true;
					}
				}
				else
				{
					return true;
				}
			}
		});

	if (it != _item_list.end())
	{
		it->get()->AddQuantity();
	}
	else
	{
		_item_list.push_back(std::make_shared<Item>(*item));
	}
}

void Inventory::RemoveFromInventory(Item* item)
{
	std::vector<std::shared_ptr<Item>>::iterator it = 
		std::find_if(_item_list.begin(), _item_list.end(), [item](const std::shared_ptr<Item>& i)
		{
			if (i->GetItemType() == item->GetItemType())
			{
				if (item->GetItemType() == ItemType::KEY)
				{
					Key& item_key = static_cast<Key&>(*item);
					Key& i_key = static_cast<Key&>(*i.get());
					if (item_key.GetKeyType() == i_key.GetKeyType())
					{
						return true;
					}
				}
				else
				{
					return true;
				}
			}
		});

	if (it != _item_list.end())
	{
		if (it->get()->GetQuantity() > 1)
		{
			it->get()->SubtractQuantity();
		}
		else
		{
			_item_list.erase(it);
		}
	}
}