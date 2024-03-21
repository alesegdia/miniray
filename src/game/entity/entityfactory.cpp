
#include "entityfactory.h"
#include <glrayfw/entity/entity.h>
#include "actor.h"
#include "mob.h"
#include <glrayfw/core/dynamicarray.h>
#include <glrayfw/physics/physics.h>
#include "controller/bulletcontroller.h"
#include "controller/moboptioncontroller.h"
#include "controller/mobaicontroller.h"
#include "controller/playerhumancontroller.h"
#include "bullet.h"
#include <glrayfw/render/sprite3d.h>
#include "../render/assets.h"
#include "pickup.h"
#include <glrayfw/entity/entitymanager.h>
#include "skill/shootskill.h"

EntityFactory::EntityFactory ()
{
	 // ctor
}

EntityFactory::~EntityFactory ()
{
}

void EntityFactory::Prepare( Physics* physics, Assets* assets, EntityManager* emanager, Transform* sceneRoot )
{
	this->physics = physics;
	this->assets = assets;
	this->sceneTree = sceneRoot;
	this->emanager = emanager;
}


Player* EntityFactory::SpawnPlayer( float x, float y ){
	Player* player = AllocEntity<Player>();
	this->player = player;

	/*
	auto skill0 = std::shared_ptr<Skill>(new ShootSkill({ 100, 10, 1000, 0, 0, 10 }, true, assets->Sprite(S3D_GREENBULLET), this, player));
	auto skill1 = std::shared_ptr<Skill>(new ShootSkill({ 10, 10, 1000, 1, 30, 10 }, true, assets->Sprite(S3D_GREENBULLET), this, player));
	auto skill2 = std::shared_ptr<Skill>(new ShootSkill({ 50, 10, 1000, 2, 30, 10 }, true, assets->Sprite(S3D_GREENBULLET), this, player));
	auto skill3 = std::shared_ptr<Skill>(new ShootSkill({ 50, 10, 1000, 3, 30, 10 }, true, assets->Sprite(S3D_GREENBULLET), this, player));
	auto skill4 = std::shared_ptr<Skill>(new ShootSkill({ 100, 10, 1000, 4, 30, 10 }, true, assets->Sprite(S3D_GREENBULLET), this, player));
	auto skill5 = std::shared_ptr<Skill>(new ShootSkill({ 10, 10, 300, 5, 30, 10 }, true, assets->Sprite(S3D_GREENBULLET), this, player));
	auto skill6 = std::shared_ptr<Skill>(new ShootSkill({ 50, 10, 300, 1, 50, 10 }, true, assets->Sprite(S3D_GREENBULLET), this, player));
	auto skill7 = std::shared_ptr<Skill>(new ShootSkill({ 50, 10, 300, 2, 50, 10 }, true, assets->Sprite(S3D_GREENBULLET), this, player));
	auto skill8 = std::shared_ptr<Skill>(new ShootSkill({ 50, 10, 300, 3, 50, 10 }, true, assets->Sprite(S3D_GREENBULLET), this, player));
	auto skill9 = std::shared_ptr<Skill>(new ShootSkill({ 50, 10, 300, 4, 50, 10 }, true, assets->Sprite(S3D_GREENBULLET), this, player));
	*/

	// pistol
	auto skill1 = std::shared_ptr<Skill>(new ShootSkill({ 300, 30, 1000, 0, 0, 10, 6 }, true, assets->Sprite(S3D_BULLETOLD), this, player));
	
	// rifle
	auto skill2 = std::shared_ptr<Skill>(new ShootSkill({ 50, 20, 1000, 0, 0, 10, 1 }, true, assets->Sprite(S3D_GREENBULLET), this, player));
	
	// shotgun
	auto skill3 = std::shared_ptr<Skill>(new ShootSkill({ 600, 30, 1000, 3, 30, 50, 1 }, true, assets->Sprite(S3D_BLUEBULLET), this, player));

	// flamethrower
	auto skill4 = std::shared_ptr<Skill>(new ShootSkill({ 50, 10, 300, 4, 30, 6, 1 }, true, assets->Sprite(S3D_FIREBALL), this, player));
	
	auto skill5 = std::shared_ptr<Skill>(new ShootSkill({ 10, 10, 300, 5, 30, 10 }, true, assets->Sprite(S3D_GREENBULLET), this, player));
	auto skill6 = std::shared_ptr<Skill>(new ShootSkill({ 50, 10, 300, 1, 50, 10 }, true, assets->Sprite(S3D_GREENBULLET), this, player));
	auto skill7 = std::shared_ptr<Skill>(new ShootSkill({ 50, 10, 300, 2, 50, 10 }, true, assets->Sprite(S3D_GREENBULLET), this, player));
	auto skill8 = std::shared_ptr<Skill>(new ShootSkill({ 50, 10, 300, 3, 50, 10 }, true, assets->Sprite(S3D_GREENBULLET), this, player));
	auto skill9 = std::shared_ptr<Skill>(new ShootSkill({ 50, 10, 300, 4, 50, 10 }, true, assets->Sprite(S3D_GREENBULLET), this, player));
	auto skill0 = std::shared_ptr<Skill>(new ShootSkill({ 100, 10, 1000, 0, 0, 10 }, true, assets->Sprite(S3D_GREENBULLET), this, player));


	player->skillSet.SetSlotSkill(0, skill0);
	player->skillSet.SetSlotSkill(1, skill1);
	player->skillSet.SetSlotSkill(2, skill2);
	player->skillSet.SetSlotSkill(3, skill3);
	player->skillSet.SetSlotSkill(4, skill4);
	player->skillSet.SetSlotSkill(5, skill5);
	player->skillSet.SetSlotSkill(6, skill6);
	player->skillSet.SetSlotSkill(7, skill7);
	player->skillSet.SetSlotSkill(8, skill8);
	player->skillSet.SetSlotSkill(9, skill9);

	player->SetSprite(NULL);
	player->SetType(Entity::Type::PLAYER);
	player->SetPhysicBody( physics->CreateSphereBody(-x*2, -y*2, reinterpret_cast<uintptr_t>(player), CollisionLayer::PLAYER, Physics::PLAYER_MASK ) );
	player->SetController( new PlayerHumanController(this, player) );

	player->hp.current = 200;
	player->hp.total = 200;

	player->skillSet.AddAmmo(300);

	return player;
}	

void EntityFactory::SpawnPlayerBullet( cml::vector2f pos, cml::vector2f dir, float time, int dmg )
{
	SpawnBullet( pos, dir, CollisionLayer::ALLY_BULLET, Physics::ABULLET_MASK, assets->Sprite(S3D_GREENBULLET), time, dmg );
}

void EntityFactory::SpawnEnemyBullet( const cml::vector2f& pos, const cml::vector2f& dir, float time, int dmg )
{
	SpawnBullet( pos, dir, CollisionLayer::ENEMY_BULLET, Physics::EBULLET_MASK, assets->Sprite(S3D_REDBULLET), time, dmg );
}

void EntityFactory::SpawnBullet(
        const cml::vector2f& pos,
        const cml::vector2f& dir,
        CollisionLayer col,
        uint16_t mask,
        Sprite3D* sprite,
        float time,
		int dmg
        )
{
	Entity* ent = AllocEntity<Bullet>();
	Bullet* bu = static_cast<Bullet*>(ent);
	bu->timer = time;
	ent->controller = new BulletController();
	ent->SetType( Entity::Type::BULLET );
	b2Body* b = physics->CreateBulletBody( pos[0], pos[1], col, mask, reinterpret_cast<uintptr_t>(ent) );
	bu->direction = b2Vec2( dir[0], dir[1] );
	bu->dmg = dmg;
	ent->SetPhysicBody(b);
	ent->SetSprite(sprite);
	ent->SetType(Entity::Type::BULLET);
	emanager->AddEntity(ent);
	this->sceneTree->AddChild(&(bu->transform));
}

class PickupController : public TypedEntityController<Pickup>
{
public:
	void Step(Pickup* p, uint32_t delta)
	{
		DoFly(p, 0.01, 0.1, 0.05);
	}

private:
};

void EntityFactory::SpawnPickup( const cml::vector2f& pos )
{
	Pickup* p = AllocEntity<Pickup>();
	p->SetPhysicBody( physics->CreateSphereBody( pos[0], pos[1], reinterpret_cast<uintptr_t>(p), CollisionLayer::PICKUP, Physics::PICKUP_MASK ) );
	p->controller = new PickupController();
	p->SetType( Entity::Type::PICKUP );
	p->SetSprite( assets->Sprite(S3D_PICKSFW) );
	emanager->AddEntity(p);
	this->sceneTree->AddChild(&(p->transform));
}

Actor* EntityFactory::SpawnEnemy( float x, float y )
{
	Mob* actor = AllocEntity<Mob>();
	ShootConfig scfg;
	scfg.cooldown = 200;
	scfg.bullet_speed = 20.f;
	scfg.bullet_duration = 1000.f;
	scfg.pushback = 0;

	std::shared_ptr<Skill> skill = std::make_shared<ShootSkill>(scfg, false, assets->Sprite(S3D_REDBULLET), this, actor);
	actor->skillSet.SetSlotSkill(0, skill);
	actor->hp.current = 10;
	actor->controller = new MobAIController();
	actor->SetSprite( assets->Sprite(S3D_BICHO) );
	actor->SetPhysicBody( physics->CreateSphereBody( -x*2, -y*2, reinterpret_cast<uintptr_t>(actor) ) );
	actor->SetRowInSpritesheet(2);
	emanager->AddEntity( actor );
	this->sceneTree->AddChild(&(actor->transform));

	Entity* weapon;
	weapon = AllocEntity<Entity>();
	weapon->SetSprite(this->assets->Sprite(S3D_FIREBALL));
	weapon->transform.local_position[0] = -1;
	weapon->controller = new MobOptionController();
	actor->transform.AddChild(&(weapon->transform));
	emanager->AddEntity(weapon);

	weapon = AllocEntity<Entity>();
	weapon->SetSprite(this->assets->Sprite(S3D_FIREBALL));
	weapon->transform.local_position[0] = 1;
	weapon->controller = new MobOptionController();
	actor->transform.AddChild(&(weapon->transform));
	emanager->AddEntity(weapon);

	weapon = AllocEntity<Entity>();
	weapon->SetSprite(this->assets->Sprite(S3D_FIREBALL));
	weapon->transform.local_position[2] = -1;
	weapon->controller = new MobOptionController();
	actor->transform.AddChild(&(weapon->transform));
	emanager->AddEntity(weapon);

	weapon = AllocEntity<Entity>();
	weapon->SetSprite(this->assets->Sprite(S3D_FIREBALL));
	weapon->transform.local_position[2] = 1;
	weapon->controller = new MobOptionController();
	actor->transform.AddChild(&(weapon->transform));
	emanager->AddEntity(weapon);
	return actor;
}

Entity* EntityFactory::SpawnPlayerWeapon(float, float)
{
	Entity* e = AllocEntity<Entity>();
	e->SetSprite( this->assets->Sprite(0) );
	return e;
}

template <typename EntityType>
EntityType* EntityFactory::AllocEntity( Transform* parent)
{
	if( parent == NULL ) parent = this->sceneTree;
	EntityType* e = new EntityType();
	// parent->AddChild( &(e->transform) );
	return e;
}



