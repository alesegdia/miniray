
#include "helpers.h"
#include "../actor.h"
#include "../mob.h"
#include "../player.h"
#include "../../constants.h"
#include "../entityfactory.h"
#include <glrayfw/physics/layers.h>
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
			entityfactory->SpawnPickup(cml::vector2f( -actor->transform.position[0], -actor->transform.position[2]));
		}
	}
}

void DoMove( Actor* actor, cml::vector3f dir, float speed, cml::vector2f postAdd)
{
	if( dir != cml::zero<3>() ) dir.normalize();
	dir *= speed;
	actor->GetPhysicBody()->SetLinearVelocity(b2Vec2(actor->pushback[0] + dir[0] + postAdd[0], actor->pushback[1] + dir[2] + postAdd[1]));
}

cml::vector2f GetWorld2DPos( cml::vector3f v )
{
	return cml::vector2f(-v[0],-v[2]);
}

cml::vector2f Rotate2D( cml::vector2f v, float angle )
{
	return cml::rotate_vector_2D( v, angle );
}

class MyRayCB : public b2RayCastCallback
{
	public:
		bool didcollide;

		void SetOrigin( )
		{
			didcollide = false;
		}

		float ReportFixture( b2Fixture* fixture, const b2Vec2&, const b2Vec2&, float )
		{
			if( fixture->GetFilterData().categoryBits == CollisionLayer::MAP )
			{
				didcollide = true;
				return 0;
			}
			return 1;
		}
};
void DoSensePlayer( Mob* actor, Player* player )
{
	cml::vector3f playerpos = player->transform.position;
	cml::vector3f mob2player = actor->transform.position - playerpos;
	float angle_to_player = 0;
	actor->player_distance = cml::length( mob2player );
	bool player_visible = false;
	if( actor->player_distance < actor->vision.distance )
	{
		cml::vector2f mob_forward = actor->GetForward();
		angle_to_player = cml::deg(cml::signed_angle_2D( mob_forward, cml::vector2f(mob2player[0],mob2player[2]) ));

			if( abs(angle_to_player) < actor->vision.angle)
			{
				// comprobamos que no haya algun elemento del mapa interrumpiendo la visión
				b2Body* b = actor->GetPhysicBody();
				cml::vector3f actorpos = actor->transform.position;
				cml::vector3f playerpos = player->transform.position;
				if( actorpos != playerpos )
				{
					MyRayCB tehcb;
					tehcb.SetOrigin();
					b2Vec2 apos(-actorpos[0],-actorpos[2]);
					b2Vec2 ppos(-playerpos[0],-playerpos[2]);

					b->GetWorld()->RayCast( &tehcb, apos, ppos );

					// si el rayo NO ha colisionado con algun elemento del mapa, tenemos al player en el cono!
					player_visible = !tehcb.didcollide;
				}
			}
	}
	//if( !player_visible ) actor->angle_to_player = NO_PLAYER;
	actor->angle_to_player = angle_to_player;
	actor->player_visible = player_visible;
}

void DoKeepDistance( Mob* mob, Player* player, uint32_t delta )
{
	mob->DoLogicAngleAdd( mob->angle_to_player );

	float dist = mob->player_distance;
	cml::vector3f mob2player = mob->transform.position - player->transform.position;
	if (dist < 6)
	{
		DoMove(mob, mob2player, -4);
	}
	else if (dist > 7)
	{
		DoMove(mob, mob2player, 4);
	}
}

void DoFly(Entity* e, double freqMod, double amplitudeMod, double offset)
{
	auto time = SDL_GetTicks();
	e->transform.position[1] = float(sin((time * freqMod)) * amplitudeMod + offset);
}
