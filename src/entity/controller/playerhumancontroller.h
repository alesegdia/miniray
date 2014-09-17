
#pragma once

#include <SDL.h>
#include <cml/cml.h>
#include "entitycontroller.h"

class Entity;


class PlayerHumanController : public EntityController {
public:
	PlayerHumanController ();
	virtual ~PlayerHumanController ();

	int HandleEvent( SDL_Event& event );
	void Step( Entity* e, uint32_t delta );


private:

	bool forward, back, left, right;
	cml::vector2f axis, rotation_offset;
	bool shift, shoot;
	float sensitivity = 0.1;


};

