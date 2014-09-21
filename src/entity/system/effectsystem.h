
#pragma once

#include "../actor.h"

class FalloutSystem {
public:
	void Step( Entity* ent, uint32_t delta )
	{
		Actor* actor = static_cast<Actor*>(ent);
		if( actor->fallout.duration >= 0 )
		{
			actor->fallout.duration -= delta;
			if( actor->fallout.last_pain <= 0 )
			{
				actor->fallout.last_pain = FALLOUT_PAIN_INTERVAL;
				actor->hp.current -= GetFalloutDamage( actor );
			}
		}
	}

private:

	void GetFalloutDamage( Actor* actor )
	{
		return 10.f/actor->stats.dkm;
	}

};

