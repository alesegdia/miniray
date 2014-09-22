
#include "contactlistener.h"
#include "../entity/entity.h"
#include "../entity/actor.h"
#include "../entity/player.h"
#include "../entity/pickup.h"

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
		if( e0->GetType() == Entity::Type::BULLET )
		{
			e0->Die();
			if( e1->GetType() == Entity::Type::MOB || e1->GetType() == Entity::Type::PLAYER )
			{
				Actor* actor = static_cast<Actor*>(e1);
				actor->hp.current--;
			}
		}
		if( e1->GetType() == Entity::Type::BULLET )
		{
			e1->Die();
			if( e0->GetType() == Entity::Type::MOB || e0->GetType() == Entity::Type::PLAYER )
			{
				Actor* actor = static_cast<Actor*>(e0);
				actor->hp.current--;
			}
		}
		if( e0->GetType() == Entity::Type::PLAYER && e1->GetType() == Entity::Type::PICKUP )
		{
			Player* pl = static_cast<Player*>( e0 );
			Pickup* pi = static_cast<Pickup*>( e1 );
			pl->ammo += pi->quantity;
			e1->Die();
		}
		if( e1->GetType() == Entity::Type::PLAYER && e0->GetType() == Entity::Type::PICKUP )
		{
			Player* pl = static_cast<Player*>( e1 );
			Pickup* pi = static_cast<Pickup*>( e0 );
			pl->ammo += pi->quantity;
			e0->Die();
		}
	}
	else if( entity0 )
	{
		Entity* e0 = static_cast<Entity*>( entity0 );
		if( e0->GetType() == Entity::Type::BULLET ) e0->Die();
	}
	else if( entity1 )
	{
		Entity* e1 = static_cast<Entity*>( entity1 );
		if( e1->GetType() == Entity::Type::BULLET ) e1->Die();
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
		//if( e0->GetType() == Entity::Type::BULLET && e1->GetType() == Entity::Type::MOB ) { e1->GetPhysicBody()->SetType( b2_dynamicBody ); }
		//if( e1->GetType() == Entity::Type::BULLET && e0->GetType() == Entity::Type::MOB ) { e0->GetPhysicBody()->SetType( b2_dynamicBody ); }
	}
}
