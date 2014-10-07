
#pragma once

#include "../actor.h"
#include "../../core/random.h"

class Actor;
class EntityFactory;
class Weapon;

void CheckHealth( Actor* actor );
bool DoShoot( Weapon* wp, bool shoot_key_pressed, uint32_t delta );
void DoDropItem( Actor* actor, RNG& rng, EntityFactory* entityfactory );
void DoMove( Actor* actor, cml::vector3f dir, float speed );
cml::vector2f GetWorld2DPos( cml::vector3f v );
cml::vector2f Rotate2D( cml::vector2f v, float angle );

cml::vector2f GetForward( Actor* actor );

