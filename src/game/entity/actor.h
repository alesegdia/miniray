
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

	bool painLastFrame = false;
	bool ammoLastFrame = false;
	bool hpLastFrame = false;

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

    SkillSet skillSet = SkillSet(10);

	void ReceiveDamage(int damage)
	{
		if (!invincible)
		{
			hp.current -= damage;
			painLastFrame = true;  
		}
		else
		{
			absorbedDamageLastFrame = true;
		}
	}

	bool invincible = false;
	bool absorbedDamageLastFrame = false;


};
