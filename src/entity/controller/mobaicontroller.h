
#pragma once

#include "entitycontroller.h"
#include "../system/healthchecker.h"
#include "../system/weaponsystem.h"
#include "../actor.h"
#include "../entity.h"
// mierda, el player deberia estar en el controller, pero bueno
#include "../system/system.h"

class MobAIController : public EntityController
{

	WeaponSystem wpsys;

public:

	void Step( Entity* e, uint32_t delta )
	{
		Actor* actor = static_cast<Actor*>(e);
		CheckHealth( actor );

		cml::vector3f mob_to_pl = actor->transform.position - System::player->transform.position;
		bool shoot = cml::length( mob_to_pl ) < 21.f;
		wpsys.TryShoot( e, &(actor->wep), shoot, delta, System::player->transform.position );
	}

};
