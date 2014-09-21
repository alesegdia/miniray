
#pragma once

#include <cml/cml.h>
#include "../core/dynamicarray.h"
#include "../physics/layers.h"

class Entity;
class Physics;
class Sprite3D;

class EntityFactory {

public:

	EntityFactory ();
	virtual ~EntityFactory ();

	void SetLists( DynamicArray<Entity*>* actorlist, DynamicArray<Entity*>* bulletlist );
	void SetPhysics( Physics* physics );
	void SetBulletSprite( Sprite3D* sprite, Sprite3D* redsprite );
	void SpawnBullet( const cml::vector2f& pos, const cml::vector2f& dir, CollisionLayer col, uint16_t mask, Sprite3D* sprite, float time );
	void SpawnPlayerBullet( cml::vector2f pos, cml::vector2f dir, float time );
	void SpawnEnemyBullet( const cml::vector2f& pos, const cml::vector2f& dir, float time );

private:

	DynamicArray<Entity*>* actorlist;
	DynamicArray<Entity*>* bulletlist;
	Physics* physics;

	// temporal hasta hacer el gestor de assets
	Sprite3D* bulletsprite;
	Sprite3D* redsprite;


};

