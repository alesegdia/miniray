
#pragma once

#include "../actor.h"
#include <glrayfw/core/random.h>

class EntityFactory;
class Weapon;
class Mob;
class Player;

// comprueba si ha muerto para marcarlo
void CheckHealth( Actor* actor );

// ejecuta el step del disparo del arma
bool DoShoot( Weapon* wp, bool shoot_key_pressed, uint32_t delta );

// dropea un objeto, solo si hay suerte
void DoDropItem( Actor* actor, RNG& rng, EntityFactory* entityfactory );

// establece la velocidad lineal
void DoMove( Actor* actor, cml::vector3f dir, float speed );

// devuelve la posicion en el mundo
cml::vector2f GetWorld2DPos( cml::vector3f v );

// rota un vector 2D
cml::vector2f Rotate2D( cml::vector2f v, float angle );

// persigue al jugador manteniendo una distancia mientras lo dispara
bool DoKeepDistanceAndShoot( Mob* mob, Player* playerpos, uint32_t delta );

// establece percepción del jugador en un enemigo
void DoSensePlayer( Mob* actor, Player* player );

// dispara hacia donde mira el actor
void Shoot( Actor* actor, EntityFactory* ef );

// girar entidad
void DoLogicAngleAdd( Actor* actor, float angle );


/*
float DealLinearDamage( Actor* attacker, Actor* victim,
		Actor::Stat::Type enforcerer, Actor::Stat::Type weakener, float factor = 1.0f
{
	//return ( attacker->stats[enforcerer] - attacker->stats[weakener] ) * factor;
	return 0;
}

float DealPhysicalDamage( Actor* attacker, Actor* victim )
{
	float dmg = 0;
	return 0;

	if( core::rng.uniform() < attacker->stats[Actor::Stat::Type::LUCK] )
		dmg = DealLinearDamage( attacker, victim, Actor::Stat::Type::POWER, Actor::Stat::Type::DEFENSE, 0.10 );

	return dmg + DealLinearDamage( attacker, victim,
			Actor::Stat::Type::POWER, Actor::Stat::Type::DEFENSE );
}

			*/
