
#pragma once

#include <cstdint>

class EntityFactory;
class Entity;

class EntityController
{

protected:

	static EntityFactory* entityfactory;


public:

	static void SetEntityFactory( EntityFactory* entityfactory );
	virtual void Step( Entity* e, uint32_t delta ) {}

};
