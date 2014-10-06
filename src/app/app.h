

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

	Camera cam;
	Map map;
	mapgen::MapData mapdata;

	Canvas* canvas;
	RNG rng;
	uint32_t deltatime;

	Assets assets;

	EntityFactory efactory;
	Player* player;
	PlayerHumanController* playercontroller;
	DynamicArray<Entity*> actors;
	DynamicArray<Entity*> bullets;

	uint32_t timer;
	float coord;
	Plane plane;
	Font font;

	tdogl::Bitmap* pbmp;

	Renderer renderer;
	Physics physics;

	void HandleCamInput();
	void GenThat();
	void PurgeList( DynamicArray<Entity*>& l );
	void SetupPlayer();
	void UpdateActors( uint32_t delta );

	// APP INTERFACE
	void Setup(int argc, char** argv);
	void Update(uint32_t delta);
	void Render();
	void Cleanup();
	void HandleEvent(SDL_Event& event);

public:

	App();

};
