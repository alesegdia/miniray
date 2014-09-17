
#include "physics.h"

void Physics::Init( int argc, char** argv )
{
	B2_NOT_USED(argc);
	B2_NOT_USED(argv);

	world = new b2World(b2Vec2(0.f,0.f));
	world->SetContactListener(&contactlistener);
}

void Physics::Cleanup()
{
	delete world;
}

b2Body* Physics::CreateBulletBody( float x, float y )
{
	// BODY CONF
	b2BodyDef bodyDef;
	bodyDef.position.Set( x, y );
	bodyDef.bullet = true;
	bodyDef.type = b2_dynamicBody;
	b2Body* body = world->CreateBody(&bodyDef);

	// SHAPE CONF
	b2CircleShape shape;
	shape.m_p.Set(0,0);
	shape.m_radius = 0.3f;

	// FIXTURE CONF
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.f;
	fixtureDef.filter.categoryBits = CollisionLayer::PLAYER_BULLET;
	fixtureDef.filter.maskBits = CollisionLayer::MAP | CollisionLayer::ENEMY;
	b2Fixture* fixture = body->CreateFixture( &fixtureDef );

	body->SetGravityScale(0);

	return body;
}

b2Body* Physics::CreateSphereBody( float x, float y )
{
	// BODY CONF
	b2BodyDef bodyDef;
	bodyDef.position.Set( x, y );
	bodyDef.type = b2_dynamicBody;
	b2Body* body = world->CreateBody(&bodyDef);

	// SHAPE CONF
	b2CircleShape shape;
	shape.m_p.Set(0,0);
	shape.m_radius = 0.7f;

	// FIXTURE CONF
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.f;
	fixtureDef.filter.categoryBits = CollisionLayer::ENEMY;
	fixtureDef.filter.maskBits = CollisionLayer::PLAYER_BULLET | CollisionLayer::MAP | CollisionLayer::ENEMY;
	b2Fixture* fixture = body->CreateFixture( &fixtureDef );

	body->SetGravityScale(0);

	return body;
}

void Physics::AddCubeBody( float x, float y )
{
	// BODY CONF
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set( x, y );
	b2Body* body = world->CreateBody(&bodyDef);

	// SHAPE CONF
	b2PolygonShape shape;
	shape.SetAsBox(1,1);

	// FIXTURE CONF
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.f;
	fixtureDef.filter.categoryBits = CollisionLayer::MAP;
	fixtureDef.filter.maskBits = CollisionLayer::PLAYER_BULLET | CollisionLayer::ENEMY;
	b2Fixture* fixture = body->CreateFixture( &fixtureDef );

}

void Physics::Step()
{
	world->Step(timeStep, velocityIterations, positionIterations);
}
