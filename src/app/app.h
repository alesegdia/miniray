

#pragma once

#include "../core/fpscounter.h"
#include "sdlglapp.h"
#include "../map/map.h"
#include "../render/camera.h"
#include "../render/block.h"
#include "../render/Bitmap.h"
#include "../render/Texture.h"
#include "../render/renderer.h"
#include "../render/assets.h"
#include "../texgen/canvas.h"
#include "../physics/physics.h"
#include "../render/plane.h"
#include "../render/font.h"
#include "../core/random.h"
#include "../entity/entityfactory.h"
#include "../map/mapdata.h"

class Player;
class PlayerHumanController;

class App : public SDLGLApp
{

private:

	// core
	RNG rng;
	uint32_t deltatime;

	// scene
	Camera cam;
	Map map;
	mapgen::MapData mapdata;					// map generation data
	Player* player;								// player entity
	PlayerHumanController* playercontroller;	// player controller for input stuff
	DynamicArray<Entity*> actors;				// list of actors
	DynamicArray<Entity*> bullets;				// list of bullets

	// game
	Assets assets;
	EntityFactory efactory;


	float coord;
	Plane plane;
	Font font;

	Renderer renderer;
	Physics physics;
	Transform sceneRoot;

	void HandleCamInput();

	void GenThat();
	void PurgeList( DynamicArray<Entity*>& l );
	void SetupPlayer();
	void UpdateActors( uint32_t delta );

	// RENDER
	void RenderMiniText();
	void RenderPlayerHP();
	void RenderWeapon();

	// APP INTERFACE
	void Setup(int argc, char** argv);
	void Update(uint32_t delta);
	void Render();
	void Cleanup();
	void HandleEvent(SDL_Event& event);

public:

	App();

};
