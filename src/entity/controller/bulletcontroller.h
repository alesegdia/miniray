
#pragma once

#include "../bullet.h"
#include "entitycontroller.h"

class BulletController : public EntityController {
public:
	void Step( Entity* e, uint32_t delta )
	{
		Bullet* b = static_cast<Bullet*>(e);
		int d = ((int)b->timer) - ((int)delta);
		if( d <= 0 ) b->Die();
		else b->timer -= delta;
	}
};

