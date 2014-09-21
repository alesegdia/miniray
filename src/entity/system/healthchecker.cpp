

#include "../actor.h"

void CheckHealth( Actor* actor )
{
	if( actor->hp.current <= 0 ) actor->Die();
}
