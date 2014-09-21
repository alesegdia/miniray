
#pragma once

#include "entitycontroller.h"

class NullController : public EntityController
{

public:

	void Step( Entity* e, uint32_t delta )
	{
		//printf("I do shit.\n");
	}

};
