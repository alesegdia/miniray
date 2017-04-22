
#pragma once

#include <glrayfw/entity/pawn.h>
#include "script/weapon.h"
#include "skill/skills.h"

class Actor : public Pawn
{

public:

	enum Faction { GOOD, BAD, NEUTRAL };
	Faction faction;

	// última vez que se aplicó daño
	int last_pain;

	// atacó en el ultimo frame?
	bool attack;

	// PWR: aumenta daño armas
	// DEF: reduccion daño armas
	// PSI: daño psi, energia magica
	// DKM: daño dkm, energia magica
	// AGI: critico, velocidad de movimiento
	struct { float pwr, def, psi, dkm, agi; } stats;

	// vida
	struct { int current, total; } hp;

	// efectos
	struct { uint32_t duration, last_pain; } fallout;
	struct { uint32_t slow, freeze, confuse; } effect;

	Weapon wep; // PUESTO AQUI PARA DEPURAR
	// EN UN FUTURO; PUNTERO A WEAPON Y EN PLAYER, PLAYERWEAPON

	void ApplyLinearVelocity()
	{
		body->SetLinearVelocity(b2Vec2(move_direction[0],move_direction[1]));
	}

    SkillSet skillSet = SkillSet(10);

};
