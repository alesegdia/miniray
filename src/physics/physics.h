
#pragma once

#include <Box2D/Box2D.h>

#include "layers.h"
#include "contactlistener.h"
#include "../core/random.h"
#include <cstdint>

class Player;


class Physics
{

private:

	const float32 timeStep = 1.0f / 60.0f;
	const int32 velocityIterations = 6;
	const int32 positionIterations = 2;
	RNG rng;

	b2World* world;
	ContactListener contactlistener;



public:

	static const uint16_t PLAYER_MASK = CollisionLayer::PICKUP | CollisionLayer::ENEMY_BULLET | CollisionLayer::MAP | CollisionLayer::ENEMY;
	static const uint16_t MOB_MASK = CollisionLayer::ALLY_BULLET | CollisionLayer::MAP | CollisionLayer::ENEMY | CollisionLayer::PLAYER;
	static const uint16_t ABULLET_MASK = CollisionLayer::MAP | CollisionLayer::ENEMY;
	static const uint16_t EBULLET_MASK = CollisionLayer::MAP | CollisionLayer::PLAYER; // | CollisionLayer::ALLY
	static const uint16_t PICKUP_MASK = CollisionLayer::PLAYER; // | CollisionLayer::ALLY

	void Init( int argc, char** argv );
	void Cleanup();
	b2Body* CreateBulletBody( float x, float y, CollisionLayer category, uint16_t mask );
	b2Body* CreateSphereBody( float x, float y, CollisionLayer category = CollisionLayer::ENEMY, uint16_t mask = MOB_MASK );
	void AddCubeBody( float x, float y );
	void Step();
	void Stress(Player*p);


};
