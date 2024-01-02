#include "stdafx.h"
#include "Item.h"

void Item::AddQuantity()
{
	++_quantity;
}

void Item::SubtractQuantity()
{
	--_quantity;
}
