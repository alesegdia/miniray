
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

	Weapon* wep; // PUESTO AQUI PARA DEPURAR
	// EN UN FUTURO; PUNTERO A WEAPON Y EN PLAYER, PLAYERWEAPON

	void ApplyLinearVelocity()
	{
		body->SetLinearVelocity(b2Vec2(move_direction[0] + pushback[0], move_direction[1] + pushback[1]));
	}

	void PushBack(int amount)
	{
		auto forward = GetForward();
		auto backward = cml::rotate_vector_2D(forward, M_PI);
		pushback = { backward[0] * amount, backward[1] * amount};
	}

	cml::vector2f GetForward()
	{
		return cml::rotate_vector_2D(cml::vector2f(0.f, 1.f), transform.logic_angle);
	}

    SkillSet skillSet = SkillSet(10);

};
