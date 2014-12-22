#pragma once
#include "entitycontroller.h"
#include "../entity.h"

class MobOptionController : public EntityController {
public:
	uint32_t time = 0;
	void Step( Entity* e, uint32_t delta )
	{
		time += delta;
		e->transform.local_position[1] = 0.4*sin(time/10.f);
		e->transform.local_rotation[0] += 0.1;
	}
};

