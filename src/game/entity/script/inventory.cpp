
#include "inventory.h"

Inventory::Inventory ()
{
	 // ctor
}

Inventory::~Inventory ()
{
	 // dtor
}


bool Inventory::AddItem( Item* item )
{
	if( item->space + space.used <= space.total )
	{
		items.Add( item );
		space.used += item->space;
		return true;
	}
	return false;
}
