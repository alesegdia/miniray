
#pragma once

#include <Box2D/Box2D.h>

#include "layers.h"
#include "contactlistener.h"


class Physics
{

private:

	const float32 timeStep = 1.0f / 60.0f;
	const int32 velocityIterations = 6;
	const int32 positionIterations = 2;

	b2World* world;
	ContactListener contactlistener;


public:

	void Init( int argc, char** argv );
	void Cleanup();
	b2Body* CreateBulletBody( float x, float y );
	b2Body* CreateSphereBody( float x, float y );
	void AddCubeBody( float x, float y );
	void Step();


};
