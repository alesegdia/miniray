
#include "entityfactory.h"
#include "entity.h"
#include "actor.h"
#include "mob.h"
#include "../core/dynamicarray.h"
#include "../physics/physics.h"
#include "controller/bulletcontroller.h"
#include "controller/mobaicontroller.h"
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
	 // dtor
}

void EntityFactory::Prepare( Physics* physics, Assets* assets, DynamicArray<Entity*>* actorlist, DynamicArray<Entity*>* bulletlist )
{
	this->actorlist = actorlist;
	this->bulletlist = bulletlist;
	this->physics = physics;
	this->assets = assets;
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
	Entity* ent = new Bullet();
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
	Pickup* p = new Pickup();
	p->SetPhysicBody( physics->CreateSphereBody( pos[0], pos[1], CollisionLayer::PICKUP, Physics::PICKUP_MASK ) );
	p->controller = NULL;
	p->SetType( Entity::Type::PICKUP );
	p->SetSprite( assets->Sprite(S3D_PICKSFW) );
	bulletlist->Add(p);
}

Actor* EntityFactory::SpawnEnemy( float x, float y )
{
	Actor* actor = new Mob();
	actor->hp.current = 10;
	actor->wep.rate = 20;
	actor->wep.bullet_speed = 20;
	actor->wep.bullet_duration = 30;
	actor->controller = new MobAIController();
	actor->SetSprite( assets->Sprite(S3D_BICHO) );
	actor->SetPhysicBody( physics->CreateSphereBody( -x*2, -y*2 ) );
	actorlist->Add( actor );
	return actor;
}
