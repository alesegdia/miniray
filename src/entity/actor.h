
#pragma once

#include "entity.h"

class ActorController;

class Actor : public Entity
{

public:

	enum Faction { GOOD, BAD, NEUTRAL };
	Faction faction;
	// offset de ángulo y dirección de movimiento
	cml::vector2f rotation_offset, move_direction;
	// última vez que se aplicó daño
	int last_pain;
	// atacó en el ultimo frame?
	bool attack;
	// fuerza, defensa y agilidad
	int pwr, def, agi;
	// vida
	int current_hp;
	int total_hp;

	void ApplyLinearVelocity()
	{
		body->SetLinearVelocity(b2Vec2(move_direction[0],move_direction[1]));
	}

};
