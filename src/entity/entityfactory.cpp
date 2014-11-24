
#include "entityfactory.h"
#include "entity.h"
#include "actor.h"
#include "mob.h"
#include "../core/dynamicarray.h"
#include "../physics/physics.h"
#include "controller/bulletcontroller.h"
#include "controller/debugtransformcontroller.h"
#include "controller/mobaicontroller.h"
#include "controller/playerhumancontroller.h"
#include "bullet.h"
#include "../render/sprite3d.h"
#include "../render/assets.h"
#include "pickup.h"

EntityFactory::EntityFactory ()
{
	 // ctor
}

EntityFactory::~EntityFactory ()
{
	for( int i = 0; i < this->rest.Size(); i++ )
	{
		delete this->rest[i];
	}
}

void EntityFactory::Prepare( Physics* physics, Assets* assets, DynamicArray<Entity*>* actorlist, DynamicArray<Entity*>* bulletlist, Transform* sceneRoot )
{
	this->actorlist = actorlist;
	this->bulletlist = bulletlist;
	this->physics = physics;
	this->assets = assets;
	this->sceneTree = sceneRoot;
}


Player* EntityFactory::SpawnPlayer( float x, float y ){
	Player* player = AllocEntity<Player>();
	this->player = player;

	
	player->SetSprite(NULL);
	player->SetType(Entity::Type::PLAYER);
	player->SetPhysicBody( physics->CreateSphereBody(-x*2, -y*2, CollisionLayer::PLAYER, Physics::PLAYER_MASK ) );
	player->SetController( new PlayerHumanController() );
	player->hp.current = 200;
	player->hp.total = 200;

}	

void EntityFactory::SpawnPlayerBullet( cml::vector2f pos, cml::vector2f dir, float time )
{
	SpawnBullet( pos, dir, CollisionLayer::ALLY_BULLET, Physics::ABULLET_MASK, assets->Sprite(S3D_GREENBULLET), time );
}

void EntityFactory::SpawnEnemyBullet( const cml::vector2f& pos, const cml::vector2f& dir, float time )
{
	SpawnBullet( pos, dir, CollisionLayer::ENEMY_BULLET, Physics::EBULLET_MASK, assets->Sprite(S3D_REDBULLET), time );
}

void EntityFactory::SpawnBullet( const cml::vector2f& pos, const cml::vector2f& dir, CollisionLayer col, uint16_t mask, Sprite3D* sprite, float time )
{
	Entity* ent = AllocEntity<Bullet>();
	Bullet* bu = static_cast<Bullet*>(ent);
	bu->timer = time;
	ent->controller = new BulletController();
	ent->SetType( Entity::Type::BULLET );
	b2Body* b = physics->CreateBulletBody( pos[0], pos[1], col, mask );
	b->SetLinearVelocity(b2Vec2( dir[0], dir[1] ));
	ent->SetPhysicBody(b);
	ent->SetSprite(sprite);
	bulletlist->Add(ent);
}

void EntityFactory::SpawnPickup( const cml::vector2f& pos )
{
	Pickup* p = AllocEntity<Pickup>();
	p->SetPhysicBody( physics->CreateSphereBody( pos[0], pos[1], CollisionLayer::PICKUP, Physics::PICKUP_MASK ) );
	p->controller = NULL;
	p->SetType( Entity::Type::PICKUP );
	p->SetSprite( assets->Sprite(S3D_PICKSFW) );
	bulletlist->Add(p);
}

Actor* EntityFactory::SpawnEnemy( float x, float y )
{
	Mob* actor = AllocEntity<Mob>();
	actor->hp.current = 10;
	actor->wep.rate = 20;
	actor->wep.bullet_speed = 20;
	actor->wep.bullet_duration = 30;
	actor->controller = new MobAIController();
	actor->SetSprite( assets->Sprite(S3D_BICHO) );
	actor->SetPhysicBody( physics->CreateSphereBody( -x*2, -y*2 ) );
	actorlist->Add( actor );
	
	
	Entity* weapon;
	weapon = AllocEntity<Entity>();
	weapon->SetSprite(this->assets->Sprite(S3D_FIREBALL));
	weapon->transform.local_position[0] = -1; 
	weapon->controller = new DebugTransformController();
	actor->transform.AddChild(&(weapon->transform));
	this->rest.Add(weapon);

	weapon = AllocEntity<Entity>();
	weapon->SetSprite(this->assets->Sprite(S3D_FIREBALL));
	weapon->transform.local_position[0] = 1; 
	weapon->controller = new DebugTransformController();
	actor->transform.AddChild(&(weapon->transform));
	this->rest.Add(weapon);

	weapon = AllocEntity<Entity>();
	weapon->SetSprite(this->assets->Sprite(S3D_FIREBALL));
	weapon->transform.local_position[2] = -1; 
	weapon->controller = new DebugTransformController();
	actor->transform.AddChild(&(weapon->transform));
	this->rest.Add(weapon);

	weapon = AllocEntity<Entity>();
	weapon->SetSprite(this->assets->Sprite(S3D_FIREBALL));
	weapon->transform.local_position[2] = 1; 
	weapon->controller = new DebugTransformController();
	actor->transform.AddChild(&(weapon->transform));
	this->rest.Add(weapon);

	
	return actor;
}

Entity* EntityFactory::SpawnPlayerWeapon(float x, float y)
{
	Entity* e = AllocEntity<Entity>();
	e->SetSprite( this->assets->Sprite(0) );
}

template <typename EntityType>
EntityType* EntityFactory::AllocEntity()
{
	EntityType* e = new EntityType();
	this->sceneTree->AddChild( &(e->transform) );
	return e;
}

void EntityFactory::UpdateRest(uint32_t delta)
{
	printf("TEHSTEP");
	for( int i = 0; i < rest.Size(); i++ )
	{
		rest[i]->Step( delta );
	}

}

void EntityFactory::RenderRest( Renderer& renderer )
{
	for( int i = 0; i < rest.Size(); i++ )
	{
		// rest[i]->PhysicStep();
		//rest[i]->transform.local_rotation[0] = cml::rad(180 + player->GetAngleY());
		rest[i]->SetAngleY( - rest[i]->transform.local_rotation[0] );//+ cml::rad(180 + player->GetAngleY()) );
		// rest[i]->transform.local_rotation[0] = -cml::rad(180 + player->GetAngleY());
		renderer.RenderEntity( rest[i] );
	}
			
}
