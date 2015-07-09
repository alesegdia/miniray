
#pragma once

#include "../bullet.h"
#include <glrayfw/entity/controller/entitycontroller.h>

class BulletController : public EntityController {
public:
	void Step( Entity* e, uint32_t delta )
	{
		Bullet* b = static_cast<Bullet*>(e);
		b->GetPhysicBody()->SetLinearVelocity(b->direction);
		int d = ((int)b->timer) - ((int)delta);
		if( d <= 0 ) b->Die();
		else b->timer -= delta;
	}
};

