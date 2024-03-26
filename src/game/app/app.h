

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

#include "../physics/contactlistener.h"



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

	virtual void PostUpdate() final
	{
		engine()->PostUpdate();
	}

	virtual void PreUpdate(uint32_t delta) final
	{
		engine()->PreUpdate(delta);
	}

	bool DoesRequestExit()
	{
		return m_requestsExit;
	}

	void SetEngine(const std::shared_ptr<Engine>& engine)
	{
		m_engine = engine;
	}

	std::shared_ptr<Screen> GetNextScreen()
	{
		return m_nextScreen;
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

	void SetNextScreen(std::shared_ptr<Screen> scr)
	{
		m_nextScreen = scr;
	}

private:
	bool m_requestsExit = false;
	std::shared_ptr<Engine> m_engine;
	std::shared_ptr<Screen> m_nextScreen = nullptr;

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
	std::shared_ptr<EntityFactory> efactory;

	void SetupPlayer();

	// RENDER
	void RenderMiniText();
	void RenderPlayerHP();
	void RenderWeapon(cml::vector3f walkOffset);


};





class MainScreen : public Screen
{
public:
	void Setup(const std::vector<std::string>& args) override
	{
		engine()->Reset(new ContactListener());
	}

	void Update(uint32_t delta) override
	{
		engine()->renderer()->Update();

	}

	void Render() override
	{
		engine()->cam()->position(cml::vector3f(0, 0, 0));
		engine()->renderer()->SetupRender();

		uint32_t time = SDL_GetTicks();
		float r = sinf((float(time)) / 10);
		float g = sinf((float(time)) / 40);
		float b = sinf((float(time)) / 40);
		engine()->renderer()->SetPlayerHealth(0.0f);
		engine()->renderer()->renderText("Miniray", -0.5, 0, cml::vector4f(r, 1, b, 1), 2, 2);


		r = sinf((float(time)) / 20);
		g = sinf((float(time)) / 20);
		b = sinf((float(time)) / 20);

		engine()->renderer()->renderText("Press enter to start game", -0.8, -0.5, cml::vector4f(r,g,b, 1), 1, 1);
	}

	void Cleanup() override
	{

	}

	void HandleEvent(SDL_Event& event) override
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_RETURN:
				SetNextScreen(std::make_shared<GameScreen>());
				break;
			}
			break;
		}

	}

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
		Assets::GetInstance().Prepare(GL());
		SetScreen(std::make_shared<MainScreen>());
	}

	void Update(uint32_t delta) override
	{
		if (m_currentScreen->GetNextScreen() != nullptr)
		{
			SetScreen(m_currentScreen->GetNextScreen());
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
		Assets::GetInstance().Clean();
	}
	
	void HandleEvent(SDL_Event& event) override
	{
		switch (event.type)
		{
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE) Stop();
			break;
		}

		m_currentScreen->HandleEvent(event);
	}

	void PostUpdate() override
	{
		if (!m_currentScreen->DoesRequestExit())
		{
			m_currentScreen->PostUpdate();
		}
	}

	void PreUpdate(uint32_t delta) override
	{
		if (!m_currentScreen->DoesRequestExit())
		{
			m_currentScreen->PreUpdate(delta);
		}
	}

	std::shared_ptr<Screen> m_currentScreen = nullptr;

};
