
#pragma once

#include "entitycontroller.h"
#include "../../constants.h"
#include "../actor.h"
#include "../mob.h"
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



public:

	void Step( Entity* e, uint32_t delta )
	{
		Mob* mob = static_cast<Mob*>(e);
		mob->GetPhysicBody()->SetLinearVelocity(b2Vec2(0,0));
		CheckHealth( mob );
		DoDropItem( mob, rng, entityfactory );
		DoSensePlayer( mob, player );

		cml::vector3f ppos = EntityController::player->transform.position;
		if( mob->player_visible )
		{
			if( DoKeepDistanceAndShoot( mob, EntityController::player, delta ) )
				Shoot( mob, entityfactory );

		}
	}

};

