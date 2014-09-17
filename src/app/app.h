

#pragma once

#include "../core/fpscounter.h"
#include "sdlglapp.h"
#include "../map/map.h"
#include "../render/camera.h"
#include "../render/block.h"
#include "../render/Bitmap.h"
#include "../render/Texture.h"
#include "../render/renderer.h"
#include "../texgen/canvas.h"
#include "../physics/physics.h"
#include "../render/plane.h"
#include "../core/random.h"

class Player;
class PlayerHumanController;

class App : public SDLGLApp
{

private:

	Camera cam;
	Map map;
	Sprite3D bichosprite, bulletsprite;
	PlayerHumanController* playercontroller;

	Canvas* canvas;
	RNG rng;
	tdogl::Bitmap* pbmp;
	tdogl::Texture *tex1, *tex2, *tex3, *suelotex, *persotex, *techotex, *bullettex;

	//FPSCounter<Uint32> fpsc;
	Player* player;
	uint32_t timer;
	float coord;
	Plane plane;
	Entity bichoentity;
	DynamicArray<Entity*> actors;
	DynamicArray<Entity*> bullets;

	Renderer renderer;
	Physics physics;

	void HandleCamInput();
	void GenThat();
	void PurgeList( DynamicArray<Entity*>& l );
	void SpawnBullet( cml::vector2f pos, cml::vector2f dir );
	void SetupPlayer();

	// APP INTERFACE
	void Setup(int argc, char** argv);
	void Update(uint32_t delta);
	void Render();
	void Cleanup();
	void HandleEvent(SDL_Event& event);

public:

	App();

};
