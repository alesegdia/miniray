
#include "entityfactory.h"
#include "entity.h"
#include "../core/dynamicarray.h"
#include "../physics/physics.h"
#include "controller/bulletcontroller.h"
#include "bullet.h"
#include "../render/sprite3d.h"

EntityFactory::EntityFactory ()
{
	 // ctor
}

EntityFactory::~EntityFactory ()
{
	 // dtor
}

void EntityFactory::SetLists( DynamicArray<Entity*>* actorlist, DynamicArray<Entity*>* bulletlist )
{
	this->actorlist = actorlist;
	this->bulletlist = bulletlist;
}

void EntityFactory::SetPhysics( Physics* physics )
{
	this->physics = physics;
}


void EntityFactory::SpawnPlayerBullet( cml::vector2f pos, cml::vector2f dir, float time )
{
	SpawnBullet( pos, dir, CollisionLayer::ALLY_BULLET, Physics::ABULLET_MASK, bulletsprite, time);
}

void EntityFactory::SpawnEnemyBullet( const cml::vector2f& pos, const cml::vector2f& dir, float time )
{
	SpawnBullet( pos, dir, CollisionLayer::ENEMY_BULLET, Physics::EBULLET_MASK, redsprite, time );
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

void EntityFactory::SetBulletSprite( Sprite3D* sprite, Sprite3D* redsprite )
{
	bulletsprite = sprite;
	this->redsprite = redsprite;
}
