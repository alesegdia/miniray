

#pragma once

#include <glrayfw/entity/entity.h>

class Pawn : public Entity
{

public:

	// offset de ángulo y dirección de movimiento
	cml::vector2f rotation_offset, move_direction;

	void ApplyLinearVelocity()
	{
		body->SetLinearVelocity(b2Vec2(move_direction[0],move_direction[1]));
	}

};
