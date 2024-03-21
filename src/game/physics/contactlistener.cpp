
#include "contactlistener.h"
#include <glrayfw/entity/entity.h>
#include "../entity/actor.h"
#include "../entity/bullet.h"
#include "../entity/player.h"
#include "../entity/pickup.h"

bool DoesCollide(Entity* e0, Entity* e1, Entity::Type ett0, Entity::Type ett1, Entity** oute0, Entity** oute1)
{
	bool hit = e0->GetType() == ett0 && e1->GetType() == ett1 ||
		       e0->GetType() == ett1 && e1->GetType() == ett0;
	*oute0 = (e0->GetType() == ett0 ? e0 : e1);
	*oute1 = (e1->GetType() == ett1 ? e1 : e0);
	return hit;
}

void ContactListener::BeginContact( b2Contact* contact )
{
	void* entity0 = reinterpret_cast<Entity*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
	void* entity1 = reinterpret_cast<Entity*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
	if( entity0 && entity1 )
	{
		Entity* e0 = static_cast<Entity*>( entity0 );
		Entity* e1 = static_cast<Entity*>( entity1 );
		e0->CollisionEnter( e1 );
		e1->CollisionEnter( e0 );
		if( e0->GetType() == Entity::Type::BULLET )
		{
			e0->Die();
			Bullet* b = static_cast<Bullet*> (e0);
			if( e1->GetType() == Entity::Type::MOB || e1->GetType() == Entity::Type::PLAYER )
			{
				Actor* actor = static_cast<Actor*>(e1);
				actor->hp.current -= b->dmg;
			}
		}
		if( e1->GetType() == Entity::Type::BULLET )
		{
			e1->Die();
			Bullet* b = static_cast<Bullet*> (e1);
			if( e0->GetType() == Entity::Type::MOB || e0->GetType() == Entity::Type::PLAYER )
			{
				Actor* actor = static_cast<Actor*>(e0);
				actor->hp.current -= b->dmg;
			}
		}
		Entity *oute0, *oute1;
		if( DoesCollide(e0, e1, Entity::Type::PLAYER, Entity::Type::PICKUP, &oute0, &oute1 ) )
		{
			Player* pl = static_cast<Player*>( oute0 );
			Pickup* pi = static_cast<Pickup*>( oute1 );
			pl->skillSet.AddAmmo(pi->quantity);
			oute1->Die();
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
	void* entity0 = reinterpret_cast<Entity*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
	void* entity1 = reinterpret_cast<Entity*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
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
