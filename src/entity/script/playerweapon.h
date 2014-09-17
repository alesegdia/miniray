
#pragma once

#include "weapon.h"

class PlayerWeapon : public Weapon
{
public:
	float SPR_per_shot;
	float BAT_per_shot;
	virtual void Shoot() {}
};
