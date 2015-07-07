

#pragma once

#include <glrayfw/core/fpscounter.h>
#include <glrayfw/app/sdlglapp.h>
#include <glrayfw/map/map.h>
#include <glrayfw/render/camera.h>
#include <glrayfw/render/block.h>
#include <glrayfw/render/Bitmap.h>
#include <glrayfw/render/Texture.h>
#include <glrayfw/render/renderer.h>
#include "../render/assets.h"
#include "../texgen/canvas.h"
#include <glrayfw/physics/physics.h>
#include <glrayfw/render/plane.h>
#include <glrayfw/render/font.h>
#include <glrayfw/core/random.h>
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

	Plane plane;
	Font font;

	Renderer renderer;
	Physics physics;
	Transform sceneRoot;

	void HandleCamInput();

	void GenThat();
	void PurgeList( DynamicArray<Entity*>& l );
	void SetupPlayer();

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
