
#pragma once

#include <glrayfw/entity/controller/entitycontroller.h>
#include "../../constants.h"
#include "../actor.h"
#include "../mob.h"
#include <glrayfw/entity/entity.h>
#include "../entityfactory.h"
#include "../player.h"
// mierda, el player deberia estar en el controller, pero bueno
#include <glrayfw/core/random.h>
#include "../script/helpers.h"

class MobAIController : public EntityController
{

	static RNG rng; // hacerlo puntero y pasarselo desde el main

	static Player* player;
	static EntityFactory* entityfactory;

public:

	static void Prepare(Player* pl, EntityFactory* ef) {
		MobAIController::player = pl;
		MobAIController::entityfactory = ef;
	}

	void Step( Entity* e, uint32_t delta )
	{
		Mob* mob = static_cast<Mob*>(e);
        assert(mob != nullptr && "THE OBJECT IS NOT A MOB");
		mob->GetPhysicBody()->SetLinearVelocity(b2Vec2(0,0));
		CheckHealth( mob );
		DoDropItem( mob, rng, entityfactory );
		DoSensePlayer( mob, player );

		if( mob->player_visible )
		{
			if( DoKeepDistanceAndShoot( mob, player, delta ) )
				Shoot( mob, entityfactory );
		}
	}

};

