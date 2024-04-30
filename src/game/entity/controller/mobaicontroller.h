
#pragma once

#include "glrayfw/entity/controller/entitycontroller.h"

#include "game/entity/entityfactory.h"
#include "game/entity/mob.h"
#include "game/entity/player.h"

#include "game/entity/script/helpers.h"
#include "glrayfw/physics/physics.h"

#include <cml/cml.h>

class FlyingController : public EntityController
{
public:
	FlyingController(double freqMod, double amplitudeMod, double offset)
		: m_freqMod(freqMod),
		  m_ampMod(amplitudeMod),
		  m_offset(offset)
	{

	}

	void Step(Entity* e, uint32_t delta)
	{
		auto time = SDL_GetTicks();
		e->transform.position[1] = float(sin((time * m_freqMod)) * m_ampMod + m_offset);
	}

private:
	double m_freqMod;
	double m_ampMod;
	double m_offset;

};

class MobAIController : public EntityController
{

	static RNG rng; // hacerlo puntero y pasarselo desde el main

	static Player* player;
	static std::shared_ptr<EntityFactory> entityfactory;

	uint32_t timeAlive = 0;

	cml::vector2f startDirection;

public:

	static void Prepare(Player* pl, const std::shared_ptr<EntityFactory>& ef) {
		MobAIController::player = pl;
		MobAIController::entityfactory = ef;

	}

	void Step(Entity* e, uint32_t delta)
	{
		Mob* mob = static_cast<Mob*>(e);

		if (timeAlive == 0)
		{
			startDirection.set(0, 1);
			auto angle = (rand() % 360) * 0.01745329251;
			startDirection = Rotate2D(startDirection, angle);
			mob->transform.logic_angle = angle;
		}

		timeAlive += delta;

		assert(mob != nullptr && "THE OBJECT IS NOT A MOB");
		mob->ClearVelocity();

		if (timeAlive < 1000)
		{
			DoMove(mob, { startDirection[0], 0, startDirection[1] }, 4);
		}

		CheckHealth(mob);
		DoDropItem(mob, rng, entityfactory);
		//DoSensePlayer(mob, player);

		if (false) //mob->player_visible || mob->painLastFrame)
		{
			DoKeepDistance(mob, player, delta);
		}
		//mob->skillSet.SetPressed(mob->player_visible);
		mob->skillSet.update(delta);
	}

};


class SpawnerAIController : public EntityController
{
public:
	SpawnerAIController(
		EntityFactory* efactory,
		std::shared_ptr<Physics> physics,
		int maxSpawnedEnemies = 10,
		uint32_t millisBetweenSpawns = 1000)
		: m_efactory(efactory),
		  m_physics(physics)
	{
		m_capacity = maxSpawnedEnemies;
		m_timeBetweenSpawns = millisBetweenSpawns;
	}

	void Step(Entity* e, uint32_t delta)
	{
		if (m_numSpawned >= m_capacity) return;
		m_timer += delta;
		if (m_timer >= m_timeBetweenSpawns)
		{
			m_timer -= m_timeBetweenSpawns;

			auto enemy = m_efactory->SpawnBasicEnemyShooter(e->transform.position[0] / 2, e->transform.position[2] / 2);
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
	int m_capacity = 10;
	uint32_t m_timeBetweenSpawns = 1000;
	uint32_t m_timer = 0;

	static RNG rng;

};




