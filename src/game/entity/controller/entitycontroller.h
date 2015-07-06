
#pragma once

#include <cstdint>

class EntityFactory;
class Entity;
class Player;

class EntityController
{

protected:

	static EntityFactory* entityfactory;
	static Player* player;


public:

	static void Prepare( EntityFactory* entityfactory, Player* player );
	virtual void Step( Entity* e, uint32_t delta ) {}

};
