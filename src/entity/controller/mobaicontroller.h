
#pragma once

#include "entitycontroller.h"
#include "../../constants.h"
#include "../actor.h"
#include "../entity.h"
#include "../entityfactory.h"
#include "../player.h"
// mierda, el player deberia estar en el controller, pero bueno
#include "../../core/random.h"
#include "../script/helpers.h"


class MobAIController : public EntityController
{

	static RNG rng; // hacerlo puntero y pasarselo desde el main

	class MyRayCB : public b2RayCastCallback
	{
		public:
			bool didcollide;

		void SetOrigin( b2Vec2 origin )
		{
			didcollide = false;
		}

		float32 ReportFixture( b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction )
		{
			if( fixture->GetFilterData().categoryBits == CollisionLayer::MAP )
			{
				didcollide = true;
				return 0;
			}
			return fraction;
		}
	};


	static constexpr float NO_PLAYER = -5000;

public:

	float PlayerInSight( Actor* actor, cml::vector3f mob2player )
	{
		//bool insight = false;
		//
		float dist = cml::length( mob2player );

		if( dist <  SIGHT_DISTANCE  )
		{
			// calculamos el ángulo desde el forward del bicho hasta el player
			cml::vector2f mob_forward = cml::rotate_vector_2D( cml::vector2f(0,1), actor->logic_angle );
			float angle2player = cml::deg(cml::signed_angle_2D( mob_forward, cml::vector2f(mob2player[0],mob2player[2]) ));

			// si entra en el cono de visión...
			if( abs(angle2player) < SIGHT_ANGLE)
			{
				// comprobamos que no haya algun elemento del mapa interrumpiendo la visión
				b2Body* b = actor->GetPhysicBody();
				cml::vector3f actorpos = actor->transform.position;
				cml::vector3f playerpos = player->transform.position;
				if( actorpos != playerpos )
				{
					MyRayCB tehcb;
					tehcb.SetOrigin(b2Vec2(actorpos[0],actorpos[2]));
					b2Vec2 apos(-actorpos[0],-actorpos[2]);
					b2Vec2 ppos(-playerpos[0],-playerpos[2]);
					b->GetWorld()->RayCast( &tehcb, apos, ppos );

					// si el rayo NO ha colisionado con algun elemento del mapa, tenemos al player en el cono!
					if( !tehcb.didcollide )
					{
						return angle2player;
					}
				}
			}
		}
		return NO_PLAYER;
	}

	void Step( Entity* e, uint32_t delta )
	{
		Actor* actor = static_cast<Actor*>(e);
		CheckHealth( actor );
		DoDropItem( actor, rng, entityfactory );

		// calculamos el vector bicho - player
		cml::vector3f mob2player = actor->transform.position - EntityController::player->transform.position;
		float dist = cml::length( mob2player );

		float angle2player = PlayerInSight( actor, mob2player );
		if( angle2player != NO_PLAYER )
		{
			bool shoot = dist < SHOOT_DISTANCE;
			actor->logic_angle += cml::rad(angle2player);
			cml::vector2f shootdir = GetForward( actor );
			if( DoShoot( &(actor->wep), shoot, delta  ) )
			{
				entityfactory->SpawnEnemyBullet( GetWorld2DPos( e->transform.position ) + shootdir, shootdir * actor->wep.bullet_speed, actor->wep.bullet_duration );
			}

			DoMove( actor, mob2player , 4 );
		}

	}

};

