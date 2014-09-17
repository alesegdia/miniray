
#include "entitycontroller.h"
#include "../entityfactory.h"

EntityFactory* EntityController::entityfactory = NULL;

void EntityController::SetEntityFactory( EntityFactory *ef )
{
	EntityController::entityfactory = ef;
}

