
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

EntityFactory::~EntityFactory ()
{

}

EntityFactory::EntityFactory( std::shared_ptr<Physics> physics, std::shared_ptr<EntityManager> emanager, std::shared_ptr<Transform> sceneRoot)
{
	this->physics = physics;
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
	auto skill1 = std::shared_ptr<Skill>(new ShootSkill({ 300, 30, 1000, 0, 0, 10, 6, 0.0001f }, true, Assets::GetInstance().Sprite("S3D_BULLETOLD"), this, player));
	
	// rifle
	auto skill2 = std::shared_ptr<Skill>(new ShootSkill({ 50, 20, 1000, 0, 0, 10, 1, 0.00003f }, true, Assets::GetInstance().Sprite("S3D_GREENBULLET"), this, player));
	
	// shotgun
	auto skill3 = std::shared_ptr<Skill>(new ShootSkill({ 600, 30, 1000, 3, 30, 50, 2, 0.001f }, true, Assets::GetInstance().Sprite("S3D_BLUEBULLET"), this, player));

	// flamethrower
	auto skill4 = std::shared_ptr<Skill>(new ShootSkill({ 50, 10, 600, 4, 30, 6, 1, 0.00001f }, true, Assets::GetInstance().Sprite("S3D_FIREBALL"), this, player));
	
	auto skill5 = std::shared_ptr<Skill>(new ShootSkill({ 10, 10, 300, 5, 30, 10 }, true, Assets::GetInstance().Sprite("S3D_GREENBULLET"), this, player));
	auto skill6 = std::shared_ptr<Skill>(new ShootSkill({ 50, 10, 300, 1, 50, 10 }, true, Assets::GetInstance().Sprite("S3D_GREENBULLET"), this, player));
	auto skill7 = std::shared_ptr<Skill>(new ShootSkill({ 50, 10, 300, 2, 50, 10 }, true, Assets::GetInstance().Sprite("S3D_GREENBULLET"), this, player));
	auto skill8 = std::shared_ptr<Skill>(new ShootSkill({ 50, 10, 300, 3, 50, 10 }, true, Assets::GetInstance().Sprite("S3D_GREENBULLET"), this, player));
	auto skill9 = std::shared_ptr<Skill>(new ShootSkill({ 50, 10, 300, 4, 50, 10 }, true, Assets::GetInstance().Sprite("S3D_GREENBULLET"), this, player));
	auto skill0 = std::shared_ptr<Skill>(new ShootSkill({ 100, 10, 1000, 0, 0, 10 }, true, Assets::GetInstance().Sprite("S3D_GREENBULLET"), this, player));


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
	player->AddController(std::make_shared<PlayerHumanController>(this, player) );

	player->hp.current = 100;
	player->hp.total = 100;

	player->skillSet.AddAmmo(300);
	player->skillSet.SetCurrentSlot(1);

	return player;
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
	ent->AddController(std::make_shared<BulletController>());
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


void EntityFactory::SpawnPickup( const cml::vector2f& pos )
{
	Pickup* p = AllocEntity<Pickup>();
	p->SetPhysicBody( physics->CreateSphereBody( pos[0], pos[1], reinterpret_cast<uintptr_t>(p), CollisionLayer::PICKUP, Physics::PICKUP_MASK ) );
	p->AddController(std::make_shared<FlyingController>(0.01, 0.1, 0.05));
	p->SetType( Entity::Type::PICKUP );
	p->type = rand() % 2 == 0 ? Pickup::Type::AMMO : Pickup::Type::HEALTH;
	p->SetSprite(Assets::GetInstance().Sprite(p->type == Pickup::Type::AMMO ? "S3D_PICKSFW" : "S3D_PICKHP"));
	emanager->AddEntity(p);
	this->sceneTree->AddChild(&(p->transform));
}

Actor* EntityFactory::SpawnBasicEnemyShooter(float x, float y)
{
	Mob* actor = AllocEntity<Mob>();
	ShootConfig scfg;
	scfg.cooldown = 300;
	scfg.bullet_speed = 15.f;
	scfg.bullet_duration = 3000.f;
	scfg.pushback = 0;
	scfg.damage = 5;

	std::shared_ptr<Skill> skill = std::make_shared<ShootSkill>(scfg, false, Assets::GetInstance().Sprite("S3D_REDBULLET"), this, actor);
	actor->skillSet.SetSlotSkill(0, skill);
	actor->hp.current = 10;
	actor->AddController(std::make_shared<MobAIController>());
	actor->SetSprite(Assets::GetInstance().Sprite("S3D_ROBOT"));
	actor->SetPhysicBody(physics->CreateSphereBody(-x * 2, -y * 2, reinterpret_cast<uintptr_t>(actor)));
	actor->SetRowInSpritesheet(2);
	emanager->AddEntity(actor);
	this->sceneTree->AddChild(&(actor->transform));

	Entity* weapon;
	weapon = AllocEntity<Entity>();
	weapon->SetSprite(Assets::GetInstance().Sprite("S3D_FIREBALL"));
	weapon->transform.local_position[0] = -1;
	weapon->AddController(std::make_shared<MobOptionController>());
	actor->transform.AddChild(&(weapon->transform));
	emanager->AddEntity(weapon);

	weapon = AllocEntity<Entity>();
	weapon->SetSprite(Assets::GetInstance().Sprite("S3D_FIREBALL"));
	weapon->transform.local_position[0] = 1;
	weapon->AddController(std::make_shared<MobOptionController>());
	actor->transform.AddChild(&(weapon->transform));
	emanager->AddEntity(weapon);

	weapon = AllocEntity<Entity>();
	weapon->SetSprite(Assets::GetInstance().Sprite("S3D_FIREBALL"));
	weapon->transform.local_position[2] = -1;
	weapon->AddController(std::make_shared<MobOptionController>());
	actor->transform.AddChild(&(weapon->transform));
	emanager->AddEntity(weapon);

	weapon = AllocEntity<Entity>();
	weapon->SetSprite(Assets::GetInstance().Sprite("S3D_FIREBALL"));
	weapon->transform.local_position[2] = 1;
	weapon->AddController(std::make_shared<MobOptionController>());
	actor->transform.AddChild(&(weapon->transform));
	emanager->AddEntity(weapon);

	actor->animationPack = Assets::GetInstance().CreateSidedAnim(2, 0);

	actor->relativeToPlayerSprite = true;
	return actor;
}

Actor* EntityFactory::SpawnBasicEnemyMelee(float x, float y)
{
	Mob* actor = AllocEntity<Mob>();
	ShootConfig scfg;
	scfg.cooldown = 300;
	scfg.bullet_speed = 15.f;
	scfg.bullet_duration = 3000.f;
	scfg.pushback = 0;
	scfg.damage = 5;

	std::shared_ptr<Skill> skill = std::make_shared<ShootSkill>(scfg, false, Assets::GetInstance().Sprite("S3D_REDBULLET"), this, actor);
	actor->skillSet.SetSlotSkill(0, skill);
	actor->hp.current = 10;
	actor->AddController(std::make_shared<MobAIController>());
	actor->SetSprite(Assets::GetInstance().Sprite("S3D_ROBOT"));
	actor->SetPhysicBody(physics->CreateSphereBody(-x * 2, -y * 2, reinterpret_cast<uintptr_t>(actor)));
	actor->SetRowInSpritesheet(2);
	emanager->AddEntity(actor);
	this->sceneTree->AddChild(&(actor->transform));

	Entity* weapon;
	weapon = AllocEntity<Entity>();
	weapon->SetSprite(Assets::GetInstance().Sprite("S3D_FIREBALL"));
	weapon->transform.local_position[0] = -1;
	weapon->AddController(std::make_shared<MobOptionController>());
	actor->transform.AddChild(&(weapon->transform));
	emanager->AddEntity(weapon);

	weapon = AllocEntity<Entity>();
	weapon->SetSprite(Assets::GetInstance().Sprite("S3D_FIREBALL"));
	weapon->transform.local_position[0] = 1;
	weapon->AddController(std::make_shared<MobOptionController>());
	actor->transform.AddChild(&(weapon->transform));
	emanager->AddEntity(weapon);

	weapon = AllocEntity<Entity>();
	weapon->SetSprite(Assets::GetInstance().Sprite("S3D_FIREBALL"));
	weapon->transform.local_position[2] = -1;
	weapon->AddController(std::make_shared<MobOptionController>());
	actor->transform.AddChild(&(weapon->transform));
	emanager->AddEntity(weapon);

	weapon = AllocEntity<Entity>();
	weapon->SetSprite(Assets::GetInstance().Sprite("S3D_FIREBALL"));
	weapon->transform.local_position[2] = 1;
	weapon->AddController(std::make_shared<MobOptionController>());
	actor->transform.AddChild(&(weapon->transform));
	emanager->AddEntity(weapon);

	actor->animationPack = Assets::GetInstance().CreateSidedAnim(2, 0);

	actor->relativeToPlayerSprite = true;
	return actor;
}

Actor* EntityFactory::SpawnBomber(float x, float y)
{
	/*
	Mob* actor = AllocEntity<Mob>();
	actor->hp.current = 10;
	actor->SetController(std::make_shared<BomberAIController>());
	actor->SetSprite(Assets::GetInstance().Sprite("S3D_ROBOT"));
	actor->SetPhysicBody(physics->CreateSphereBody(-x * 2, -y * 2, reinterpret_cast<uintptr_t>(actor)));
	actor->SetRowInSpritesheet(2);
	emanager->AddEntity(actor);
	this->sceneTree->AddChild(&(actor->transform));
	*/
	return nullptr;
}


Entity* EntityFactory::SpawnEntity(const EntityPrefab& prefab, float x, float y)
{
	Entity* actor = AllocEntity<Entity>();
	actor->SetType(prefab.entityType);
	auto sprite = Assets::GetInstance().Sprite(prefab.spriteID);
	actor->SetSprite(sprite);
	actor->SetPhysicBody(physics->CreateSphereBody(-x * 2, -y * 2, reinterpret_cast<uintptr_t>(actor), prefab.collisionLayer, prefab.collisionMask, prefab.dynamicBody));
	actor->AddController(prefab.controller);
	emanager->AddEntity(actor);
	this->sceneTree->AddChild(&(actor->transform));
	return actor;
}

Entity* EntityFactory::SpawnSpawner(float x, float y)
{
	EntityPrefab prefab;
	prefab.collisionLayer = CollisionLayer::ENEMY_UNDMG;
	prefab.collisionMask = CollisionLayer::PLAYER | CollisionLayer::ENEMY;
	prefab.controller = std::make_shared<SpawnerAIController>(this, physics);
	prefab.dynamicBody = false;
	prefab.entityType = Entity::Type::SPAWNER;
	prefab.spriteID = "S3D_SPAWNER";
	auto entity = SpawnEntity(prefab, x, y);
	entity->name = "SPAWNER";
	entity->animationPack = Assets::GetInstance().CreateOneSidedAnim(1, 0);
	return entity;
}

Entity* EntityFactory::SpawnPortal(float x, float y)
{
	Entity* actor = AllocEntity<Entity>();
	actor->SetType(Entity::Type::PORTAL);
	actor->SetSprite(Assets::GetInstance().Sprite("S3D_PORTAL"));
	actor->SetPhysicBody(physics->CreateSphereBody(-x*2, -y*2, reinterpret_cast<uintptr_t>(actor), CollisionLayer::PORTAL, Physics::PORTAL_MASK, true));
	emanager->AddEntity(actor);
	this->sceneTree->AddChild(&(actor->transform));
	actor->AddController(std::make_shared<FlyingController>(0.002, 0.1, 0.025));

	return actor;
}

template <typename EntityType>
EntityType* EntityFactory::AllocEntity( Transform* parent)
{
	if( parent == NULL ) parent = this->sceneTree.get();
	EntityType* e = new EntityType();
	// parent->AddChild( &(e->transform) );
	return e;
}



