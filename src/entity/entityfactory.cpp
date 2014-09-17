
#include "entityfactory.h"
#include "entity.h"
#include "../core/dynamicarray.h"
#include "../physics/physics.h"

EntityFactory::EntityFactory ()
{
	 // ctor
}

EntityFactory::~EntityFactory ()
{
	 // dtor
}

void EntityFactory::SetLists( DynamicArray<Entity*>* actorlist, DynamicArray<Entity*>* bulletlist )
{
	this->actorlist = actorlist;
	this->bulletlist = bulletlist;
}

void EntityFactory::SetPhysics( Physics* physics )
{
	this->physics = physics;
}
