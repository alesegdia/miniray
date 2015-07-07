
#pragma once

#include <glrayfw/entity/entity.h>
#include "actor.h"

class Bullet : public Entity {
public:
	Bullet() {
		this->type = Entity::Type::BULLET;
	}
	Actor* owner;
	float dmg;
	int effect;
	int element;
	uint32_t timer = 5;
};

