
#pragma once

#include <cml/cml.h>
#include "../core/dynamicarray.h"
#include "../physics/layers.h"

class Entity;
class Player;
class Physics;
class Sprite3D;
class Assets;
class Actor;

class EntityFactory {

public:

	EntityFactory ();
	virtual ~EntityFactory ();

	void Prepare(
			Physics* physics, Assets* assets,
			DynamicArray<Entity*>* actorlist,
			DynamicArray<Entity*>* bulletlist
		);

	Player* SpawnPlayer( float x, float y );
	void SpawnBullet( const cml::vector2f& pos, const cml::vector2f& dir, CollisionLayer col, uint16_t mask, Sprite3D* sprite, float time );
	void SpawnPlayerBullet( cml::vector2f pos, cml::vector2f dir, float time );
	void SpawnEnemyBullet( const cml::vector2f& pos, const cml::vector2f& dir, float time );
	void SpawnPickup( const cml::vector2f& pos );
	Entity* SpawnPlayerWeapon( float x, float y );
	Actor* SpawnEnemy( float x, float y );


private:

	DynamicArray<Entity*>* actorlist;
	DynamicArray<Entity*>* bulletlist;
	Physics* physics;
	Assets* assets;
	Transform* sceneTree;


};

