
#pragma once

#include "../actor.h"
#include "../../core/random.h"

class Actor;
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

// obtener vector hacia delante
cml::vector2f GetForward( Actor* actor );

