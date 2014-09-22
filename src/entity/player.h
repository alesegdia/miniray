
#pragma once

#include "actor.h"
#include "script/playerweapon.h"

class Inventory;

class Player : public Actor
{

public:

	// se pulsó la tecla de inventario en el último frame?
	bool inventory_open;
	// durabilidad, si llega a 0 se rompe el SFW
	float BAT;
	// energia SPR, cada SFW consume N x SPR por Disparo
	float SPR;
	// script de inventario
	Inventory* inventory;
	// arma en uso
	PlayerWeapon weapon; // ES UN PUNTERO!! CAMBIADO PARA TESTEAR!!
	// velocidad al andar
	float walk_speed = 8.f;
	// velocidad al esprintar
	float run_speed = 16.f;
	int ammo = 200;

};
