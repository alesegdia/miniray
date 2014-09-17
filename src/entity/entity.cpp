

#include "entity.h"
#include "controller/entitycontroller.h"

void Entity::SetController( EntityController* controller )
{
	this->controller = controller;
}

void Entity::Step( uint32_t delta )
{
	if( this->controller )
	{
		this->controller->Step( this, delta );
	}
}

