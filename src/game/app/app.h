

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

class Screen
{
public:
	virtual ~Screen() {}
	virtual void Update(uint32_t delta) = 0;

	virtual void Render() = 0;

	virtual void Setup(const std::vector<std::string>& args) = 0;

	virtual void Cleanup() = 0;

	virtual void HandleEvent(SDL_Event& event) = 0;

	bool DoesRequestExit()
	{
		return m_requestsExit;
	}

	void SetEngine(const std::shared_ptr<Engine>& engine)
	{
		m_engine = engine;
	}

protected:
	void RequestExit()
	{
		m_requestsExit = true;
	}

	const std::shared_ptr<Engine>& engine()
	{
		return m_engine;
	}

private:
	bool m_requestsExit = false;
	std::shared_ptr<Engine> m_engine;

};


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
	Assets assets;
	EntityFactory efactory;

	Font font;
	Scene scene;

	void SetupPlayer();

	// RENDER
	void RenderMiniText();
	void RenderPlayerHP();
	void RenderWeapon(cml::vector3f walkOffset);


};


class App : public SDLGLApp
{
public:

    App(int w, int h);


    virtual ~App();

	void SetScreen(std::shared_ptr<Screen> newScreen)
	{
		if (m_currentScreen != nullptr)
		{
			m_currentScreen->Cleanup();
		}
		m_currentScreen = newScreen;
		m_currentScreen->SetEngine(engine());
		m_currentScreen->Setup(GetArgs());
	}

private:

	// APP INTERFACE
	void Setup(const std::vector<std::string>& args) override
	{
		SetScreen(std::make_shared<GameScreen>());
	}

	void Update(uint32_t delta) override
	{
		if (m_currentScreen->DoesRequestExit())
		{
			Stop();
		}
		else
		{
			m_currentScreen->Update(delta);
		}
	}

	void Render() override
	{
		m_currentScreen->Render();
	}

	void Cleanup() override
	{
		m_currentScreen->Cleanup();
	}
	
	void HandleEvent(SDL_Event& event) override
	{
		m_currentScreen->HandleEvent(event);
	}

	std::shared_ptr<Screen> m_currentScreen = nullptr;

};
