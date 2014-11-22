#pragma once
#include "entitycontroller.h"

class DebugTransformController : public EntityController {
public:
	void Step( Entity* e, uint32_t delta )
	{
		printf("%f\n", e->transform.local_position[0]);
	}
};

