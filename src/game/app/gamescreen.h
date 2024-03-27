

#pragma once

#include <glrayfw/core/fpscounter.h>
#include <glrayfw/app/sdlglapp.h>

#include "screen.h"
#include "game/map/mapgen.h"

class Player;
class PlayerHumanController;
class EntityFactory;


class GameScreen : public Screen
{
public:
	virtual ~GameScreen()
	{

	}

	void Setup(const std::vector<std::string>& args) override;

	void Update(uint32_t delta) override;

	void Render() override;

	void Cleanup() override;

	void HandleEvent(SDL_Event& event) override;


private:
	// core
	RNG rng;

	// scene
	mapgen::MapData mapdata;					// map generation data
	Player* player;								// player entity
	PlayerHumanController* playercontroller;	// player controller for input stuff

	// game
	std::shared_ptr<EntityFactory> efactory;

	void SetupPlayer();

	// RENDER
	void RenderMiniText();
	void RenderPlayerHP();
	void RenderWeapon(cml::vector3f walkOffset);


};


