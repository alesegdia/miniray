
#include "system.h"
#include "../entityfactory.h"
#include "../entity.h"

EntityFactory* System::entityfactory = NULL;

void System::SetEntityFactory(EntityFactory *efact)
{
	System::entityfactory = efact;
}

Entity* System::player = NULL;

void System::SetPlayerEntity(Entity *p)
{
	System::player = p;
}
