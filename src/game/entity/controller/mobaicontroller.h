
#pragma once

#include "glrayfw/entity/controller/entitycontroller.h"

#include "game/entity/entityfactory.h"
#include "game/entity/mob.h"
#include "game/entity/player.h"

#include "game/entity/script/helpers.h"
#include "glrayfw/physics/physics.h"

class MobAIController : public EntityController
{

	static RNG rng; // hacerlo puntero y pasarselo desde el main

	static Player* player;
	static EntityFactory* entityfactory;

public:

	static void Prepare(Player* pl, EntityFactory* ef) {
		MobAIController::player = pl;
		MobAIController::entityfactory = ef;
	}

	void Step(Entity* e, uint32_t delta)
	{
		Mob* mob = static_cast<Mob*>(e);
		assert(mob != nullptr && "THE OBJECT IS NOT A MOB");
		mob->ClearVelocity();
		CheckHealth(mob);
		DoDropItem(mob, rng, entityfactory);
		DoSensePlayer(mob, player);

		if (mob->player_visible || mob->painLastFrame)
		{
			DoKeepDistance(mob, player, delta);
		}
		mob->skillSet.SetPressed(mob->player_visible);
		mob->skillSet.update(delta);
	}

};


class SpawnerAIController : public EntityController
{
public:
	SpawnerAIController(EntityFactory* efactory, std::shared_ptr<Physics> physics)
		: m_efactory(efactory),
		  m_physics(physics)
	{

	}

	void Step(Entity* e, uint32_t delta)
	{
		if (m_numSpawned >= m_capacity) return;
		m_timer += delta;
		if (m_timer >= m_timeBetweenSpawns)
		{
			m_timer -= m_timeBetweenSpawns;

			/*

			bool canSpawn = false;
			
			cml::vector2f positionToSpawn;

			while (!canSpawn)
			{
				positionToSpawn[0] = - e->transform.position[0];
				positionToSpawn[1] = - e->transform.position[2];
				canSpawn = true;
				if (!m_physics->IsAnyBodyDetected({ {positionToSpawn[0] - SPAWN_WIDTH, positionToSpawn[1] - SPAWN_WIDTH}, {SPAWN_WIDTH, SPAWN_WIDTH} }))
				{
					canSpawn = true;
				}
			}
			*/

			auto enemy = m_efactory->SpawnEnemy(e->transform.position[0] / 2, e->transform.position[2] / 2);
			m_numSpawned++;
			enemy->onDie = [this](Entity* e) {
				this->m_numSpawned--;
			};
		}
	}

private:

	float m_xdiff = 3.0f;
	float m_ydiff = 3.0f;
	static constexpr float SPAWN_WIDTH = 0.1f;

	EntityFactory* m_efactory;
	std::shared_ptr<Physics> m_physics;

	int m_numSpawned = 0;
	int m_capacity = 6;
	uint32_t m_timeBetweenSpawns = 5000;
	uint32_t m_timer = 0;

	static RNG rng; // hacerlo puntero y pasarselo desde el main

};

