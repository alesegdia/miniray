
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


public:

	void Step( Entity* e, uint32_t delta )
	{
		Mob* mob = static_cast<Mob*>(e);
		mob->GetPhysicBody()->SetLinearVelocity(b2Vec2(0,0));
		CheckHealth( mob );
		DoDropItem( mob, rng, entityfactory );
		DoSensePlayer( mob, player );

		if( mob->player_visible )
		{
			if( DoKeepDistanceAndShoot( mob, EntityController::player, delta ) )
				Shoot( mob, entityfactory );
		}
	}

};

