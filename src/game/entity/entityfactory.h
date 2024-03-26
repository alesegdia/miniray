
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

	EntityFactory (std::shared_ptr<Physics> physics, std::shared_ptr<EntityManager> emanager, std::shared_ptr<Transform> sceneRoot);
	virtual ~EntityFactory ();


	template <typename EntityType>
	EntityType* AllocEntity(Transform* parent=NULL);

	Player* SpawnPlayer( float x, float y );
	void SpawnBullet( const cml::vector2f& pos, const cml::vector2f& dir, CollisionLayer col, uint16_t mask, Sprite3D* sprite, float time, int dmg);
	void SpawnPickup( const cml::vector2f& pos);
	Actor* SpawnEnemy(float x, float y);
	Entity* SpawnPortal(float x, float y);


private:

	std::shared_ptr<Physics> physics;
	std::shared_ptr<Transform> sceneTree;
	std::shared_ptr<EntityManager> emanager;


};


