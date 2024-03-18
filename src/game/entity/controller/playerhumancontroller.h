
#pragma once

#include <SDL.h>
#include <cml/cml.h>
#include <glrayfw/entity/controller/entitycontroller.h>

class Entity;
class EntityFactory;


class PlayerHumanController : public EntityController {
public:
	PlayerHumanController (EntityFactory* efactory);
	virtual ~PlayerHumanController ();

	int HandleEvent( SDL_Event& event );
	void Step( Entity* e, uint32_t delta );


private:

	EntityFactory* entityfactory;
	bool forward, back, left, right;
	cml::vector2f axis, rotation_offset;
	bool shift, shoot;
	float sensitivity = 0.1;
	cml::vector2i lastMousePos;


};

