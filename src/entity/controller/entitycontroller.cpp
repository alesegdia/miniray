
#include "entitycontroller.h"
#include "../entityfactory.h"
#include "../player.h"

EntityFactory* EntityController::entityfactory = NULL;
Player* EntityController::player = NULL;

void EntityController::Prepare( EntityFactory *ef, Player* player )
{
	EntityController::entityfactory = ef;
	EntityController::player = player;
}

