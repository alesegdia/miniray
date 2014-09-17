
#include "contactlistener.h"
#include "../entity/entity.h"

void ContactListener::BeginContact( b2Contact* contact )
{
	void* entity0 = contact->GetFixtureA()->GetBody()->GetUserData();
	void* entity1 = contact->GetFixtureB()->GetBody()->GetUserData();
	if( entity0 && entity1 )
	{
		Entity* e0 = static_cast<Entity*>( entity0 );
		Entity* e1 = static_cast<Entity*>( entity1 );
		e0->CollisionEnter( e1 );
		e1->CollisionEnter( e0 );
		if( e0->GetType() == CollisionLayer::PLAYER_BULLET && e1->GetType() != CollisionLayer::PLAYER && e1->GetType() != CollisionLayer::PLAYER_BULLET ) e0->Die();
		if( e1->GetType() == CollisionLayer::PLAYER_BULLET && e0->GetType() != CollisionLayer::PLAYER && e0->GetType() != CollisionLayer::PLAYER_BULLET ) e1->Die();
	}
	else if( entity0 )
	{
		Entity* e0 = static_cast<Entity*>( entity0 );
		if( e0->GetType() == CollisionLayer::PLAYER_BULLET )
			e0->Die();
	}
	else if( entity1 )
	{
		Entity* e1 = static_cast<Entity*>( entity1 );
		if( e1->GetType() == CollisionLayer::PLAYER_BULLET )
			e1->Die();
	}
}

void ContactListener::EndContact( b2Contact* contact )
{
	void* entity0 = contact->GetFixtureA()->GetBody()->GetUserData();
	void* entity1 = contact->GetFixtureB()->GetBody()->GetUserData();
	if( entity0 && entity1 )
	{
		Entity* e0 = static_cast<Entity*>( entity0 );
		Entity* e1 = static_cast<Entity*>( entity1 );
		e0->CollisionExit( e1 );
		e1->CollisionExit( e0 );
	}
}
