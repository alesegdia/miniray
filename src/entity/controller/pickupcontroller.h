
#pragma once

#include "entitycontroller.h"

class PickupController : public EntityController {
public:

	void Step( Entity* e, uint32_t delta )
	{
		Pickup* p = static_cast<Pickup*>(e);
	}

};

