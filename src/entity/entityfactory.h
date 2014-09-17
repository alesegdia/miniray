
#pragma once

#include "../core/dynamicarray.h"

class Entity;
class Physics;

class EntityFactory {

public:

	EntityFactory ();
	virtual ~EntityFactory ();

	void SetLists( DynamicArray<Entity*>* actorlist, DynamicArray<Entity*>* bulletlist );
	void SetPhysics( Physics* physics );

private:

	DynamicArray<Entity*>* actorlist;
	DynamicArray<Entity*>* bulletlist;
	Physics* physics;


};

