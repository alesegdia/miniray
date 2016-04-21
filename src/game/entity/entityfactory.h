
#pragma once

#include <cml/cml.h>
#include <glrayfw/core/dynamicarray.h>
#include <glrayfw/physics/layers.h>
#include <glrayfw/render/renderer.h>

class Entity;
class Player;
class Physics;
class Sprite3D;
class Assets;
class Actor;
class Transform;
class EntityManager;

class EntityFactory {
	
private:
	
	Player* player;

public:

	EntityFactory ();
	virtual ~EntityFactory ();

	void Prepare(
			Physics* physics, Assets* assets,
			EntityManager* emanager,
			Transform* sceneRoot
		);

	template <typename EntityType>
	EntityType* AllocEntity(Transform* parent=NULL);

	Player* SpawnPlayer( float x, float y );
	void SpawnBullet( const cml::vector2f& pos, const cml::vector2f& dir, CollisionLayer col, uint16_t mask, Sprite3D* sprite, float time );
	void SpawnPlayerBullet( cml::vector2f pos, cml::vector2f dir, float time );
	void SpawnEnemyBullet( const cml::vector2f& pos, const cml::vector2f& dir, float time );
	void SpawnPickup( const cml::vector2f& pos );
	Entity* SpawnPlayerWeapon(float, float);
	Actor* SpawnEnemy( float x, float y );


private:

	Physics* physics;
	Assets* assets;
	Transform* sceneTree;
	EntityManager* emanager;


};

