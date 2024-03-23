

#pragma once

#include <glrayfw/core/fpscounter.h>
#include <glrayfw/app/sdlglapp.h>
#include <glrayfw/render/camera.h>
#include <glrayfw/render/block.h>
#include <glrayfw/render/Bitmap.h>
#include <glrayfw/render/Texture.h>
#include "../render/assets.h"
#include "../texgen/canvas.h"
#include <glrayfw/render/plane.h>
#include <glrayfw/render/font.h>
#include <glrayfw/core/random.h>
#include "../entity/entityfactory.h"
#include "../map/mapdata.h"

class Player;
class PlayerHumanController;

class App : public SDLGLApp
{
public:

    App(int w, int h);


    virtual ~App();


private:

	// core
	RNG rng;
	uint32_t deltatime;

	// scene
    mapgen::MapData mapdata;					// map generation data
	Player* player;								// player entity
	PlayerHumanController* playercontroller;	// player controller for input stuff

	// game
	Assets assets;
	EntityFactory efactory;

	Font font;
    Scene scene;

	void HandleCamInput();

	void GenThat();
	void SetupPlayer();

	// RENDER
	void RenderMiniText();
	void RenderPlayerHP();
	void RenderWeapon(cml::vector3f walkOffset);

	// APP INTERFACE
	void Setup(int argc, char** argv);
	void Update(uint32_t delta);
	void Render();
	void Cleanup();
	void HandleEvent(SDL_Event& event);

};
