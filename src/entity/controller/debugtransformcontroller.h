#pragma once
#include "entitycontroller.h"
#include "../entity.h"

class DebugTransformController : public EntityController {
public:
	uint32_t time = 0;
	void Step( Entity* e, uint32_t delta )
	{
		time += delta;
		printf("time: %d\n", delta);
		e->transform.local_position[1] = 0.4*sin(time/10.f);
		printf("%f\n", e->transform.local_position[0]);
		e->transform.local_rotation[0] += 0.1;
	}
};

