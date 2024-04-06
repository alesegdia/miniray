
#pragma once

#include "actor.h"
#include "script/playerweapon.h"

class Inventory;


struct PowerUp
{
	int weaponIndexUpgrade = -1;
	int speedLevel = -1;
};

// health kills you but you heal on parrying

struct Stats
{
	float walkSpeed = 4.f;
	float runSpeed = 8.f;
	int parryCooldown = 2300;
	int parryingTime = 300;
	int slowdownTimeOnParry = 1000;
	void ApplyPowerup(PowerUp pwup)
	{

	}
};

/*
std::vector<PowerUp> CreateAllPowerups()
{
	std::vector<PowerUp> allPowerups;
	std::vector<std::string> weaponNames = { "pistol", "shotgun", "rifle", "thrower" };
	for (int i = 0; i < weaponNames.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			PowerUp pwup;
			pwup.weaponIndexUpgrade = i;
			allPowerups.push_back(pwup);
		}
	}

	return allPowerups;
}
*/

class Player : public Actor
{

public:

	void ApplyPowerup(const PowerUp& powerUp)
	{
		int result = skillSet.UpgradeSkill(powerUp.weaponIndexUpgrade);
	}

	// se pulsó la tecla de inventario en el último frame?
	bool inventory_open;
	// durabilidad, si llega a 0 se rompe el SFW
	float BAT;
	// energia SPR, cada SFW consume N x SPR por Disparo
	float SPR;
	// script de inventario
	Inventory* inventory;
	
	int parryTimer = -1;

	// cooldown tiene que ser mayor que parryingTime porque pasan a la vez los dos timers por simplicitud
	int parryCooldownTimer = -1;

	int slowdownTimer = 0;

	bool touchPortal = false;

	Stats stats;


};
