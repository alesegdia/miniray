
#pragma once

#include <SDL.h>
#include <cml/cml.h>
#include <glrayfw/entity/controller/entitycontroller.h>

class Entity;
class EntityFactory;
class Player;

class PlayerHumanController : public EntityController {
public:
	PlayerHumanController (EntityFactory* efactory, Player* player);
	virtual ~PlayerHumanController ();

	int HandleEvent( SDL_Event& event );
	void Step( Entity* e, uint32_t delta );


private:
	bool parryingRequested = false;

	EntityFactory* entityfactory;
	bool forward, back, left, right;
	cml::vector2f axis, rotation_offset;
	bool shift, shoot;
	float sensitivity = 0.1;
	cml::vector2i lastMousePos = { 400, 300 };

	Player* m_player;


	bool m_isDashing = false;
	cml::vector2f m_currentDashSpeed = { 0,0 };
	float m_dashDecay = 0.7f;
	bool m_dashPressed = false;
	float m_dashPower = 80.0f;
	float m_dashPowerBase = 80.0f;
	float m_dashPowerSlowdown = 2000.0f;

};

