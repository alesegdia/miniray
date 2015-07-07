
#pragma once

#include <cstdint>

class Entity;

class EntityController
{

protected:


public:

	virtual void Step( Entity* e, uint32_t delta ) {}

};
