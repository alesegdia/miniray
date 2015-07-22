#pragma once
#include <glrayfw/entity/controller/entitycontroller.h>
#include <glrayfw/entity/entity.h>

class MobOptionController : public EntityController {
public:
	uint32_t time = 0;
	void Step( Entity* e, uint32_t delta )
	{
		time += delta;
		e->transform.local_position[1] = 0.4*sin(time/100.f);
		e->transform.local_rotation[0] += delta * 0.001;
	}
};

