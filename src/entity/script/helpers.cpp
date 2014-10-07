
#include "helpers.h"
#include "../actor.h"
#include "../entityfactory.h"
#include "weapon.h"

void CheckHealth( Actor* actor )
{
	if( actor->hp.current <= 0 ) actor->Die();
}

void DoDropItem( Actor* actor, RNG& rng, EntityFactory* entityfactory )
{
	if( !actor->IsAlive() )
	{
		if( rng.uniform() > 0.6 )
		{
			printf("SUERTO!\n");
			printf("%f, %f\n", actor->transform.position[0], actor->transform.position[2]);
			entityfactory->SpawnPickup(cml::vector2f( -actor->transform.position[0], -actor->transform.position[2]));
		}
	}
}

bool DoShoot( Weapon* wp, bool shoot_key_pressed, uint32_t delta )
{
	if( shoot_key_pressed )
	{
		if( wp->last_shot >= wp->rate )
		{
			wp->last_shot = 0;
			return true;
		}
		else
		{
			wp->last_shot += delta;
		}
	}
	else
	{
		wp->last_shot += delta;
	}
	return false;

}

void DoMove( Actor* actor, cml::vector3f dir, float speed )
{
	if( dir != cml::zero<3>() ) dir.normalize();
	dir *= speed;
	actor->GetPhysicBody()->SetLinearVelocity(b2Vec2(dir[0],dir[2]));
}

cml::vector2f GetWorld2DPos( cml::vector3f v )
{
	return cml::vector2f(-v[0],-v[2]);
}

cml::vector2f GetForward( Actor* actor )
{
	return cml::rotate_vector_2D( cml::vector2f(0.f,1.f), actor->logic_angle );
}
cml::vector2f Rotate2D( cml::vector2f v, float angle )
{
	return cml::rotate_vector_2D( v, angle );
}
