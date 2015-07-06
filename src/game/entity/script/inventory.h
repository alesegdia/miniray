
#pragma once

#include "../../core/dynamicarray.h"

typedef struct
{
	enum Type
	{
		SFW
	};
	int space;
} Item;

class Inventory {
public:
	Inventory ();
	virtual ~Inventory ();

	bool AddItem( Item* item );

private:
	DynamicArray<Item*> items;
	struct {
		int used;
		int total;
	} space;
};

